var server = "css3.ps";
var generate = function(){};
var generate2 = function(){};
var all_function = function() {
////////////////////////////////////////////////////////////////

/**
 * codePoint - an integer containing a Unicode code point
 * return - the number of bytes required to store the code point in UTF-8
 */
function utf8Len(codePoint) {
    if(codePoint >= 0xD800 && codePoint <= 0xDFFF) {
        throw new Error("Illegal argument: "+codePoint);
    }
    if(codePoint < 0) { throw new Error("Illegal argument: "+codePoint); }
    if(codePoint <= 0x7F) { return 1; }
    if(codePoint <= 0x7FF) { return 2; }
    if(codePoint <= 0xFFFF) { return 3; }
    if(codePoint <= 0x1FFFFF) { return 4; }
    if(codePoint <= 0x3FFFFFF) { return 5; }
    if(codePoint <= 0x7FFFFFFF) { return 6; }
    throw new Error("Illegal argument: "+codePoint);
}

function isHighSurrogate(codeUnit) {
    return codeUnit >= 0xD800 && codeUnit <= 0xDBFF;
}

function isLowSurrogate(codeUnit) {
    return codeUnit >= 0xDC00 && codeUnit <= 0xDFFF;
}

/**
 * Transforms UTF-16 surrogate pairs to a code point.
 * See RFC2781
 */
function toCodepoint(highCodeUnit, lowCodeUnit) {
    if(!isHighSurrogate(highCodeUnit)) { throw new Error("Illegal argument: "+highCodeUnit); }
    if(!isLowSurrogate(lowCodeUnit)) { throw new Error("Illegal argument: "+lowCodeUnit); }
    highCodeUnit = (0x3FF & highCodeUnit) << 10;
    var u = highCodeUnit | (0x3FF & lowCodeUnit);
    return u + 0x10000;
}

/**
 * Counts the length in bytes of a string when encoded as UTF-8.
 * str - a string
 * return - the length as an integer
 */
function utf8ByteCount(str) {
    var count = 0;
    for(var i=0; i<str.length; i++) {
        var ch = str.charCodeAt(i);
        if(isHighSurrogate(ch)) {
            var high = ch;
            var low = str.charCodeAt(++i);
            count += utf8Len(toCodepoint(high, low));
        } else {
            count += utf8Len(ch);
        }
    }
    return count;
}

////////////////////////////////////////////////////////////////

function isSpace(str) {
    return str == " " || str == "\t" || str == "\r" || str == "\n";
}

function trim(str) {
    while (str.length && isSpace(str.charAt(0))) {
        str = str.substr(1);
    }
    while (str.length && isSpace(str.charAt(str.length - 1))) {
        str = str.substr(0, str.length - 1);
    }
    return str;
}

////////////////////////////////////////////////////////////////

function createMultiPartUtf8FileRequest(host, scriptName, boundary, fieldName, fileName, data) {
    var body = "--" + boundary + "\n";
    body += "Content-Disposition: form-data; name=\"" + fieldName + "\"\n";
    body += "Content-Transfer-Encoding: binary\n";
	body += "\n";
    body += data;
	body += "\n";
	body += "--" + boundary + "--\n";

    var headers = "POST http://" + host + scriptName + " HTTP/1.1\n";
    headers += "Host: " + host + "\n";
    headers += "Content-Type: multipart/form-data; boundary=" + boundary + "\n";
    headers += "Content-Length: " + utf8ByteCount(body) + "\n\n";

    return headers + body;
}

function getRequestBoundary(data) {
    var result = "--boundary";
    var counter = 0;

    while (data.indexOf(result) >= 0) {
        result += counter;
        ++counter;
    }

    return result;
}

function createStylesRequest(id, styles) {
    return createMultiPartUtf8FileRequest(server, "/Handler.ashx?id=" + id + "&version=1.0.158",
        getRequestBoundary(styles), "xml", "styles.xml", styles);
}

function readLineFromSocket(socket) {
    var str = "";

    var c = socket.read(1);
    while (c != "\n") {
        if (c == "") {
            throw new Error("Timeout during reading response from the server");
        }
        str += c;
        c = socket.read(1);
    }

    return str;
}

function readHttpHeadersFromSocket(socket) {
    var contentLength = 0;

    while (true) {
        var str = readLineFromSocket(socket).toLowerCase();
        if (str == "") {
            if (!contentLength) {
                throw new Error("Failed to read http-headers");
            }
            return contentLength;
        }
        if (str.indexOf("content-length") >= 0) {
            var parts = str.split(":");
            if (parts.length != 2) {
                throw new Error("Incorrect header content-length '" + str + "'");
            }
            contentLength = parseInt(trim(parts[1]));
        }
    }
}

/**
 *  We can't use here socket.read(contentLength) because socket removes symbols \r which were counted in  contentLength
 */
function readHttpBodyFromSocket(socket, contentLength) {
    var read = 0;
    var body = "";
    while (read < contentLength) {
        var c = socket.read(1);
        if (c == "") {
            throw new Error("Timeout during reading response from the server");
        }
        body += c;

        if (c == "\n") {
            ++read; // Counting \r
        }
        ++read;
    }
    return body;
}

function sendHttpRequest(host, port, request) {
    var socket = new Socket;
    try {
        if (!socket.open(host + ":" + port, "UTF-8")) {
            throw new Error("Failed to open socket with '" + host + "'");
        }

        socket.timeout = 30;
        socket.write(request);
        var contentLength = readHttpHeadersFromSocket(socket);
        return trim(readHttpBodyFromSocket(socket, contentLength));
    }
    catch (e) {
        socket.close();
        throw e;
    }
}

function sendStyles(id, styles) {
    return sendHttpRequest(server, 80, createStylesRequest(id, styles));
}

////////////////////////////////////////////////////////////////

function openBrowser(id, url) {
  var fname = "css3ps-" + id + ".url";
  var shortcut = new File(Folder.temp + '/' + fname);
  shortcut.open('w');
  shortcut.writeln('[InternetShortcut]');
  shortcut.writeln('URL=' + url);
  shortcut.writeln();
  shortcut.close();
  shortcut.execute();
  //shortcut.remove();
}

////////////////////////////////////////////////////////////////

XML.prettyPrinting = false;

function createTag(name, data) {
    var result = new XML("<" + name + "></" + name + ">");
    result.appendChild(data);
    return result;
}

/*
 This fake variable is used only not to have a lot of single line constructions of type
 if (!obj.typename) {
        return createTag("nulltypename", obj);
    }

 because js minifier converts them in
 !obj.typename) ? createTag("nulltypename", obj) : ...

 and photoshop works incorrectly with long list of such cases
 */
var fake_counter = 0;

function makeXMLForObject(obj) {
    if (typeof(obj) == "undefined") {
        ++fake_counter;
        return new XML("<null></null>");
    }
    if (!obj.typename) {
        ++fake_counter;
        return createTag("nulltypename", obj);
    }
    if (obj.typename == 'ActionDescriptor') {
        ++fake_counter;
        return makeXMLForActionDescriptor(obj);
    }
    if (obj.typename == 'ActionReference') {
        ++fake_counter;
        return makeXMLForActionReference(obj);
    }
    if (obj.typename == 'ActionList') {
        ++fake_counter;
        return makeXMLForActionList(obj);
    }
    return createTag("unsupported", obj.typename);
}

function makeXmlForValue(obj, key) {
    if (obj.getType(key) == DescValueType.INTEGERTYPE) {
        ++fake_counter;
        return createTag("value", obj.getInteger(key));
    }
    if (obj.getType(key) == DescValueType.STRINGTYPE) {
        ++fake_counter;
        return createTag("value", obj.getString(key));
    }
    if (obj.getType(key) == DescValueType.DOUBLETYPE) {
        ++fake_counter;
        return createTag("value", obj.getDouble(key));
    }
    if (obj.getType(key) == DescValueType.BOOLEANTYPE) {
        ++fake_counter;
        return createTag("value", obj.getBoolean(key));
    }
    if (obj.getType(key) == DescValueType.ENUMERATEDTYPE) {
        ++fake_counter;
        return createTag("type", typeIDToStringID(obj.getEnumerationType(key))) +
            createTag("value", typeIDToStringID(obj.getEnumerationValue(key)));
    }
    if (obj.getType(key) == DescValueType.UNITDOUBLE) {
        ++fake_counter;
        return createTag("type", typeIDToStringID(obj.getUnitDoubleType(key))) +
            createTag("value", obj.getUnitDoubleValue(key));
    }
    if (obj.getType(key) == DescValueType.LISTTYPE) {
        ++fake_counter;
        return makeXMLForActionList(obj.getList(key));
    }
    if (obj.getType(key) == DescValueType.OBJECTTYPE) {
        ++fake_counter;
        return makeXMLForObject(obj.getObjectValue(key));
    }
    if (obj.getType(key) == DescValueType.REFERENCETYPE) {
        ++fake_counter;
        return makeXMLForActionReference(obj.getReference(key));
    }

    return createTag("unsupported", obj.getType(key));
}

function makeXmlForSubObject(obj, key, indexed) {
    var type = obj.getType(key);

    var result = new XML();
    if (indexed) {
        result = new XML('<element type="' + type + '" id="' + key + '"></element>');
    }
    else {
        result = new XML('<element type="' + type + '" charid="' + typeIDToCharID(key) + '" stringid="' +
            typeIDToStringID(key) + '"></element>');
    }

    result.appendChild(makeXmlForValue(obj, key));
    return result;
}

function makeXMLForActionReference(ar) {
    return new XML("<reference></reference>");
}

function makeXMLForActionList(al) {
    var result = new XML("<list></list>");
    for (var i = 0; i < al.count; ++i) {
        try {
            result.appendChild(makeXmlForSubObject(al, i, true));
        }
        catch (e) {
            result.appendChild(createTag("error", e));
        }
    }
    return result;
}

function makeXMLForActionDescriptor(ad) {
    var result = new XML("<descriptor></descriptor>");
    for (var i = 0; i < ad.count; ++i) {
        try {
            result.appendChild(makeXmlForSubObject(ad, ad.getKey(i), false));
        }
        catch (e) {
            result.appendChild(createTag("error", e));
        }
    }
    return result;
}

function getLayerStylesXML(idx) {
    var ref = new ActionReference();
    ref.putIndex(charIDToTypeID("Lyr "), idx);
    var desc = executeActionGet(ref);
    return makeXMLForObject(desc);
}

function getCurrentLayerStylesXML() {
    var ref = new ActionReference();
    ref.putEnumerated(charIDToTypeID("Lyr "), charIDToTypeID("Ordn"), charIDToTypeID("Trgt"));
    var desc = executeActionGet(ref);
    return makeXMLForObject(desc);
}

function getPathXML() {
    try {
        var ref = new ActionReference();
        ref.putEnumerated(charIDToTypeID("Path"), charIDToTypeID("Path"), stringIDToTypeID("vectorMask"));
        var desc = executeActionGet(ref);
        return createTag("path", makeXMLForObject(desc));
    }
    catch (e) {
        return createTag("path", createTag("error", e));
    }
}

function getInfoXML(){
    var result = new XML("<info><xmlversion>1</xmlversion><ourversion>1.0.158</ourversion></info>");
    try {
        result.appendChild(createTag("filename", $.filename));
        result.appendChild(createTag("build", $.build));
        result.appendChild(createTag("include", $.includePath));
        result.appendChild(createTag("locale", $.locale));
        result.appendChild(createTag("os", $.os));
        result.appendChild(createTag("version", $.version));
    } catch (e) {
        result.appendChild(createTag("error", e));
    }
    return result;
}

function copySelectedLayers() {
    try {
        var desc = new ActionDescriptor();
        var refDoc = new ActionReference();
        refDoc.putClass(charIDToTypeID("Dcmn"));
        desc.putReference(charIDToTypeID("null"), refDoc);

        var refLayer = new ActionReference();
        refLayer.putEnumerated(charIDToTypeID("Lyr "), charIDToTypeID("Ordn"), charIDToTypeID("Trgt"));
        desc.putReference(charIDToTypeID("Usng"), refLayer );
        executeAction(charIDToTypeID("Mk  "), desc, DialogModes.NO);
    } catch (e) {
        // Happens when there is no opened document or selected layers
        return false;
    }

    return true;
}

function closeCurrentDocument() {
    var desc = new ActionDescriptor();
    desc.putEnumerated(charIDToTypeID("Svng"), charIDToTypeID("YsN "), charIDToTypeID("N   "));
    executeAction(charIDToTypeID("Cls "), desc, DialogModes.NO);
}

function getGlobalAngle() {
    try {
        var ref = new ActionReference();
        ref.putProperty(charIDToTypeID("Prpr"), charIDToTypeID("gblA"));
        ref.putEnumerated(charIDToTypeID("Lyr "), charIDToTypeID("Ordn"), charIDToTypeID("Trgt"));
        var desc = executeActionGet(ref);
        return desc.getInteger(charIDToTypeID("gblA"));
    } catch (e) {
    }
    return undefined;
}

function setGlobalAngle(angle) {
    if (typeof(angle) == "undefined") {
        return;
    }
    try {
        var desc = new ActionDescriptor();
        var ref = new ActionReference();
        ref.putProperty(charIDToTypeID('Prpr'), charIDToTypeID('Lefx') );
        ref.putEnumerated(charIDToTypeID('Lyr '), charIDToTypeID('Ordn'), charIDToTypeID('Trgt') );
        desc.putReference(charIDToTypeID('null'), ref);

        var ldesc = new ActionDescriptor();
        ldesc.putUnitDouble(charIDToTypeID("gagl"), charIDToTypeID("#Ang"), angle);

        desc.putObject(charIDToTypeID('T   '), charIDToTypeID('Lefx'), ldesc);

        executeAction(charIDToTypeID('setd'), desc, DialogModes.NO);
    }
    catch (e) {
    }
}

function traverseLayers(layers, xml, timesXml, globalAngle) {
    // After copying layers to new document, all layers become selected and setGlobalAngle failed for
    // first layer because app.activeDocument.activeLayer = layer[0]; doesn't reset selection but any other layer reset selection
    if (layers.length > 1)
        app.activeDocument.activeLayer = layers[layers.length - 1];

    for (var i = 0; i < layers.length; i++) {
        try {
            var layer = layers[i];
            if (layer.typename == "LayerSet") {
                traverseLayers(layer.layers, xml, timesXml, globalAngle);
            }
            else {
                timesXml.appendChild(createTag("start_layer", new Date().toString()));
                app.activeDocument.activeLayer = layer;
                setGlobalAngle(globalAngle);
                var styles = getCurrentLayerStylesXML();
                var path = getPathXML();
                xml.appendChild(createTag("layer", styles + path));
                timesXml.appendChild(createTag("end_layer", new Date().toString()));
            }
        } catch (e) {
            xml.appendChild(createTag("layer", createTag("error", e)));
        }
    }
}

function traverseAllLayers(timesXml, globalAngle) {
    timesXml.appendChild(createTag("start_all_layers", new Date().toString()));
    var xml = new XML("<layers></layers>");
    traverseLayers(app.activeDocument.layers, xml, timesXml, globalAngle);
    timesXml.appendChild(createTag("end_all_layers", new Date().toString()));
    return xml;
}

function cleanUp(newDocument) {
    if (newDocument) {
        closeCurrentDocument()
    }
    else {
        //app.activeDocument.activeLayer = null;
    }
}

function getSelectedLayersStylesXML() {
    if (!documents.length)
        return "<data><layers></layers></data>";
    var info = getInfoXML();

    var times = new XML("<times></times>");
    times.appendChild(createTag("start_get_selection", new Date().toString()));

    var globalAngle = getGlobalAngle(); // Copy from the old document to new

    var newDocument = copySelectedLayers();

    if (!newDocument) {
        globalAngle = undefined; // To not to update it current document
    }

    times.appendChild(createTag("end_get_selection", new Date().toString()));

    var result = new XML();

    try {
        result = traverseAllLayers(times, globalAngle);
    } catch (e) {
        result.appendChild(createTag("error", e));
    }
    cleanUp(newDocument);

    info.appendChild(times);
    return createTag("data", info + result).toXMLString();
}


////////////////////////////////////////////////////////////////

function S4() {
   return (((1+Math.random())*0x10000)|0).toString(16).substring(1);
}
function guid() {
   return (S4()+S4()+"-"+S4()+"-"+S4()+"-"+S4()+"-"+S4()+S4()+S4());
}

generate = function() {
    try {
        var styles = getSelectedLayersStylesXML();
        return "<object><property id=\"styles\"><string>" + styles + "</string></property></object>";
    }
    catch (e) {
        return "<object><property id=\"error\"><string>" + e + "</string></property></object>";
    }
};

generate2 = function() {
    try {
        var id = guid();
        openBrowser(id, "http://" + server + "/?=" + id);
        var styles = getSelectedLayersStylesXML();
        sendStyles(id, styles);
    } catch (e) {
        alert("Error occurred:\n" + e);
    }
};

////////////////////////////////////////////////////////////////

function saveFile(name, data) {
    var file = new File (name);
    try
    {
        file.open("w:");
        file.writeln(data);
    }
    catch (e) {
        file.close();
        throw e;
    }
    file.close();
}
};

all_function();
generate2();