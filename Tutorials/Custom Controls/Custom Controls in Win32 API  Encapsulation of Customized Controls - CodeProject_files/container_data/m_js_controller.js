(function(_){var ba,fa,ka,na,pa,va,wa,Aa,Da,C,Ta,Ua,Va,Xa,ab,ib,lb,pb,qb,zb,Ab,Db,Eb,Fb,Kb,Mb,Lb,Qb,Sb,Tb,Ub,Vb,Wb,Yb,Xb,Zb,ac,$b,bc,ec,fc,gc,hc,ic,kc,mc,qc,pc,uc,yc,Ac,Bc,Cc,Ec,Fc,Gc,Hc,Ic,Lc,Mc,Kc,Jc,Dc,Nc,Oc,Qc,Uc,Wc,Xc,Yc,$c,ad,ed,cd,fd,jd,ld,kd,nd,od,pd,sd,vd,yd,zd,Bd,Cd,Dd,Fd,ha,Gd,ia,Ld,Md;ba=function(a){return function(){return _.aa[a].apply(this,arguments)}};_.ca=function(a){var b=0;return function(){return b<a.length?{done:!1,value:a[b++]}:{done:!0}}};_.ea=function(a){var b="undefined"!=typeof Symbol&&Symbol.iterator&&a[Symbol.iterator];return b?b.call(a):{next:_.ca(a)}};fa=function(a){if(!(a instanceof Array)){a=_.ea(a);for(var b,c=[];!(b=a.next()).done;)c.push(b.value);a=c}return a};ka=function(a,b){a.prototype=ha(b.prototype);a.prototype.constructor=a;if(ia)ia(a,b);else for(var c in b)if("prototype"!=c)if(Object.defineProperties){var d=Object.getOwnPropertyDescriptor(b,c);d&&Object.defineProperty(a,c,d)}else a[c]=b[c];a.W=b.prototype};na=function(a,b){if(b){var c=_.la;a=a.split(".");for(var d=0;d<a.length-1;d++){var e=a[d];e in c||(c[e]={});c=c[e]}a=a[a.length-1];d=c[a];b=b(d);b!=d&&null!=b&&(0,_.ma)(c,a,{configurable:!0,writable:!0,value:b})}};pa=function(a,b){this.b=a;(0,_.ma)(this,"description",{configurable:!0,writable:!0,value:b})};_.q=function(a,b,c){a=a.split(".");c=c||_.p;a[0]in c||"undefined"==typeof c.execScript||c.execScript("var "+a[0]);for(var d;a.length&&(d=a.shift());)a.length||void 0===b?c[d]&&c[d]!==Object.prototype[d]?c=c[d]:c=c[d]={}:c[d]=b};_.qa=function(){};_.ra=function(a){var b=typeof a;if("object"==b)if(a){if(a instanceof Array)return"array";if(a instanceof Object)return b;var c=Object.prototype.toString.call(a);if("[object Window]"==c)return"object";if("[object Array]"==c||"number"==typeof a.length&&"undefined"!=typeof a.splice&&"undefined"!=typeof a.propertyIsEnumerable&&!a.propertyIsEnumerable("splice"))return"array";if("[object Function]"==c||"undefined"!=typeof a.call&&"undefined"!=typeof a.propertyIsEnumerable&&!a.propertyIsEnumerable("call"))return"function"}else return"null";else if("function"==b&&"undefined"==typeof a.call)return"object";return b};_.sa=function(a){return"array"==_.ra(a)};_.ta=function(a){return"function"==_.ra(a)};_.ua=function(a){var b=typeof a;return"object"==b&&null!=a||"function"==b};va=function(a,b,c){return a.call.apply(a.bind,arguments)};wa=function(a,b,c){if(!a)throw Error();if(2<arguments.length){var d=Array.prototype.slice.call(arguments,2);return function(){var e=Array.prototype.slice.call(arguments);Array.prototype.unshift.apply(e,d);return a.apply(b,e)}}return function(){return a.apply(b,arguments)}};_.t=function(a,b,c){Function.prototype.bind&&-1!=Function.prototype.bind.toString().indexOf("native code")?_.t=va:_.t=wa;return _.t.apply(null,arguments)};_.v=function(a,b){var c=Array.prototype.slice.call(arguments,1);return function(){var d=c.slice();d.push.apply(d,arguments);return a.apply(this,d)}};_.y=function(a,b){function c(){}c.prototype=b.prototype;a.W=b.prototype;a.prototype=new c;a.prototype.constructor=a};_.ya=function(a,b){b=(0,_.xa)(a,b);var c;(c=0<=b)&&Array.prototype.splice.call(a,b,1);return c};_.za=function(a){var b=a.length;if(0<b){for(var c=Array(b),d=0;d<b;d++)c[d]=a[d];return c}return[]};Aa=function(a){var b=!1,c;return function(){b||(c=a(),b=!0);return c}};Da=function(a,b){this.g=a===Ba&&b||"";this.l=Ca};_.Ea=function(a){return a instanceof Da&&a.constructor===Da&&a.l===Ca?a.g:"type_error:Const"};_.z=function(a){return new Da(Ba,a)};_.A=function(a,b){this.l=a===_.Fa&&b||"";this.v=Ga};_.Ha=function(a){if(a instanceof _.A&&a.constructor===_.A&&a.v===Ga)return a.l;_.ra(a);return"type_error:TrustedResourceUrl"};_.B=function(a,b){this.l=a===_.Ia&&b||"";this.v=Ja};_.Ka=function(a){if(a instanceof _.B&&a.constructor===_.B&&a.v===Ja)return a.l;_.ra(a);return"type_error:SafeUrl"};_.Ma=function(a){if(a instanceof _.B)return a;a="object"==typeof a&&a.Y?a.b():String(a);La.test(a)||(a="about:invalid#zClosurez");return new _.B(_.Ia,a)};C=function(a){return-1!=Na.indexOf(a)};_.Pa=function(){this.l="";this.A=Oa;this.v=null};_.Qa=function(a){if(a instanceof _.Pa&&a.constructor===_.Pa&&a.A===Oa)return a.l;_.ra(a);return"type_error:SafeHtml"};_.Ra=function(a,b){var c=new _.Pa;c.l=a;c.v=b;return c};Ta=function(a){var b=new _.A(_.Fa,_.Ea(Sa));a.src=_.Ha(b).toString()};Ua=function(){return C("iPhone")&&!C("iPod")&&!C("iPad")};Va=function(a){Va[" "](a);return a};_.Wa=function(a,b){try{return Va(a[b]),!0}catch(c){}return!1};Xa=function(){var a=_.p.document;return a?a.documentMode:void 0};_.E=function(){};_.F=function(a,b,c){a.b=null;b||(b=[]);a.C=void 0;a.v=-1;a.g=b;a:{if(b=a.g.length){--b;var d=a.g[b];if(!(null===d||"object"!=typeof d||_.sa(d)||Ya&&d instanceof Uint8Array)){a.A=b-a.v;a.l=d;break a}}a.A=Number.MAX_VALUE}a.B={};if(c)for(b=0;b<c.length;b++)if(d=c[b],d<a.A)d+=a.v,a.g[d]=a.g[d]||Za;else{var e=a.A+a.v;a.g[e]||(a.l=a.g[e]={});a.l[d]=a.l[d]||Za}};_.$a=function(a,b){if(b<a.A){b+=a.v;var c=a.g[b];return c===Za?a.g[b]=[]:c}if(a.l)return c=a.l[b],c===Za?a.l[b]=[]:c};_.G=function(a,b,c){a=_.$a(a,b);return null==a?c:a};_.H=function(a,b){a=_.$a(a,b);a=null==a?a:!!a;return null==a?!1:a};_.I=function(a,b,c){a.b||(a.b={});if(!a.b[c]){var d=_.$a(a,c);d&&(a.b[c]=new b(d))}return a.b[c]};ab=function(a,b,c){a.b||(a.b={});if(!a.b[c]){for(var d=_.$a(a,c),e=[],f=0;f<d.length;f++)e[f]=new b(d[f]);a.b[c]=e}b=a.b[c];b==Za&&(b=a.b[c]=[]);return b};_.bb=function(a){if(a.b)for(var b in a.b){var c=a.b[b];if(_.sa(c))for(var d=0;d<c.length;d++)c[d]&&_.bb(c[d]);else c&&_.bb(c)}return a.g};_.db=function(a){_.F(this,a,cb)};_.eb=function(a){return _.G(a,22,"")};_.fb=function(a){return _.G(a,23,"")};_.gb=function(a){_.F(this,a,null)};ib=function(a){_.F(this,a,null)};_.kb=function(a){_.F(this,a,null)};lb=function(a){_.F(this,a,null)};pb=function(a){_.F(this,a,nb)};qb=function(a){return ab(a,_.db,1)};_.rb=function(a,b){this.b=void 0!==a?a:0;this.g=void 0!==b?b:0};_.sb=function(a,b){b=String(b);"application/xhtml+xml"===a.contentType&&(b=b.toLowerCase());return a.createElement(b)};_.tb=function(a){var b=a.indexOf("#");0>b&&(b=a.length);var c=a.indexOf("?");if(0>c||c>b){c=b;var d=""}else d=a.substring(c+1,b);return[a.substr(0,c),d,a.substr(b)]};_.ub=function(a,b){return b?a?a+"&"+b:b:a};_.vb=function(a,b){if(!b)return a;a=_.tb(a);a[1]=_.ub(a[1],b);return a[0]+(a[1]?"?"+a[1]:"")+a[2]};_.wb=function(a,b,c){if(_.sa(b))for(var d=0;d<b.length;d++)_.wb(a,String(b[d]),c);else null!=b&&c.push(a+(""===b?"":"="+encodeURIComponent(String(b))))};_.xb=function(a){var b=[],c;for(c in a)_.wb(c,a[c],b);return b.join("&")};_.yb=function(a,b){b=_.xb(b);return _.vb(a,b)};zb=function(a){try{return!!a&&null!=a.location.href&&_.Wa(a,"foo")}catch(b){return!1}};Ab=function(a,b){if(a)for(var c in a)Object.prototype.hasOwnProperty.call(a,c)&&b.call(void 0,a[c],c,a)};_.Bb=function(a){a.preventDefault?a.preventDefault():a.returnValue=!1};Db=function(a){return a?a.passive&&Cb()?a:a.capture||!1:!1};_.K=function(a,b,c,d){a.addEventListener&&a.addEventListener(b,c,Db(d))};Eb=function(a,b,c){a.removeEventListener&&a.removeEventListener(b,c,Db(void 0))};_.Gb=function(a,b,c){Fb(a,b,void 0===c?null:c)};Fb=function(a,b,c){a.google_image_requests||(a.google_image_requests=[]);var d=a.document.createElement("img");if(c){var e=function(f){c&&c(f);Eb(d,"load",e);Eb(d,"error",e)};_.K(d,"load",e);_.K(d,"error",e)}d.src=b;a.google_image_requests.push(d)};Kb=function(a,b){var c=_.Hb(599);b=b instanceof _.B||!Ib.test(b)?b:new _.B(_.Ia,b);_.Jb(b,c);c=b instanceof _.B?b:_.Ma(b);a.href=_.Ka(c)};_.Jb=function(a,b){"about:invalid#zClosurez"===(a instanceof _.B?a:_.Ma(a)).b()&&b(String(a))};_.Hb=function(a){var b=(Lb()?"http:":"https:")+"//pagead2.googlesyndication.com/pagead/gen_204";return function(c){c=_.yb(b,{id:"unsafeurl",ctx:a,url:c});navigator.sendBeacon&&navigator.sendBeacon(c,"")}};Mb=function(a,b){for(var c in a)Object.prototype.hasOwnProperty.call(a,c)&&b.call(void 0,a[c],c,a)};_.Ob=function(a,b,c,d,e,f,g){if(!g)a:{if(1===a.nodeType)try{if(1==a.nodeType){c:{try{var h=a.getBoundingClientRect()}catch(r){var m={left:0,top:0,right:0,bottom:0};break c}if(_.Nb&&a.ownerDocument.body){var l=a.ownerDocument;h.left-=l.documentElement.clientLeft+l.body.clientLeft;h.top-=l.documentElement.clientTop+l.body.clientTop}m=h}g=new _.rb(m.left,m.top)}else{var n=a.changedTouches?a.changedTouches[0]:a;g=new _.rb(n.clientX,n.clientY)}break a}catch(r){}g=new _.rb(0,0)}if(document.createEvent)m=document.createEvent("MouseEvents"),m.initMouseEvent("click",!0,!0,null,0,g.b,g.g,g.b,g.g,c,f,d,e,b,null);else return!1;if(a.dispatchEvent)a.dispatchEvent(m);else return!1;return!0};Lb=function(){var a=void 0===a?_.L:a;return"http:"===a.location.protocol};_.Pb=function(a,b,c){c=void 0===c?_.M:c;switch(a){case 2:return c.getElementsByClassName(b);case 3:return c.getElementsByTagName(b)}return[]};_.N=function(a,b,c){c=void 0===c?_.M:c;switch(a){case 1:if(c.getElementById)return c.getElementById(b);break;case 2:case 3:if(a=_.Pb(a,b,c),0<a.length)return a[0]}return null};Qb=function(a,b){a&&Mb(b,function(c,d){a.style[d]=c})};_.Rb=function(a){a=_.ea(a);for(var b=a.next();!b.done;b=a.next())if(b=b.value,"use_refactored_boomerang_click_handler"===_.G(b,1,"")&&"true"===_.G(b,2,"").toLowerCase())return!0;return!1};Sb=function(a,b){var c=void 0===c?{}:c;this.error=a;this.context=b.context;this.msg=b.message||"";this.id=b.id||"jserror";this.meta=c};Tb=function(a,b){this.b=a;this.g=b};Ub=function(a,b){this.url=a;this.Na=!!b;this.depth=null};Vb=function(){this.l="&";this.v=!1;this.g={};this.A=0;this.b=[]};Wb=function(a,b){var c={};c[a]=b;return[c]};Yb=function(a,b,c,d,e){var f=[];Ab(a,function(g,h){(g=Xb(g,b,c,d,e))&&f.push(h+"="+g)});return f.join(b)};Xb=function(a,b,c,d,e){if(null==a)return"";b=b||"&";c=c||",$";"string"==typeof c&&(c=c.split(""));if(a instanceof Array){if(d=d||0,d<c.length){for(var f=[],g=0;g<a.length;g++)f.push(Xb(a[g],b,c,d+1,e));return f.join(c[d])}}else if("object"==typeof a)return e=e||0,2>e?encodeURIComponent(Yb(a,b,c,d,e+1)):"...";return encodeURIComponent(String(a))};Zb=function(a,b,c,d){a.b.push(b);a.g[b]=Wb(c,d)};ac=function(a,b,c){b=b+"//pagead2.googlesyndication.com"+c;var d=$b(a)-c.length;if(0>d)return"";a.b.sort(function(n,r){return n-r});c=null;for(var e="",f=0;f<a.b.length;f++)for(var g=a.b[f],h=a.g[g],m=0;m<h.length;m++){if(!d){c=null==c?g:c;break}var l=Yb(h[m],a.l,",$");if(l){l=e+l;if(d>=l.length){d-=l.length;b+=l;e=a.l;break}a.v&&(e=d,l[e-1]==a.l&&--e,b+=l.substr(0,e),e=a.l,d=0);c=null==c?g:c}}a="";null!=c&&(a=e+"trn="+c);return b+a};$b=function(a){var b=1,c;for(c in a.g)b=c.length>b?c.length:b;return 3997-b-a.l.length-1};bc=function(){this.g=Lb()?"http:":"https:";this.b=Math.random()};ec=function(){var a=cc,b=dc.google_srt;0<=b&&1>=b&&(a.b=b)};fc=function(a,b,c,d,e,f){if((d?a.b:Math.random())<(e||.01))try{if(c instanceof Vb)var g=c;else g=new Vb,Ab(c,function(m,l){var n=g,r=n.A++;m=Wb(l,m);n.b.push(r);n.g[r]=m});var h=ac(g,a.g,"/pagead/gen_204?id="+b+"&");h&&("undefined"===typeof f?_.Gb(_.p,h):_.Gb(_.p,h,f))}catch(m){}};gc=function(){var a=_.p.performance;return a&&a.now&&a.timing?Math.floor(a.now()+a.timing.navigationStart):(0,_.O)()};hc=function(){var a=void 0===a?_.p:a;return(a=a.performance)&&a.now?a.now():null};ic=function(a,b,c){this.label=a;this.type=b;this.value=c;this.duration=0;this.uniqueId=Math.random();this.slotId=void 0};kc=function(){var a=dc;this.events=[];this.g=a||_.p;var b=null;a&&(a.google_js_reporting_queue=a.google_js_reporting_queue||[],this.events=a.google_js_reporting_queue,b=a.google_measure_js_timing);this.b=jc()||(null!=b?b:1>Math.random())};mc=function(a){a&&lc&&jc()&&(lc.clearMarks("goog_"+a.label+"_"+a.uniqueId+"_start"),lc.clearMarks("goog_"+a.label+"_"+a.uniqueId+"_end"))};_.oc=function(){var a=nc;this.v=cc;this.g=null;this.B=this.l;this.b=void 0===a?null:a;this.A=!1};qc=function(a,b,c){try{if(a.b&&a.b.b){var d=a.b.start(b.toString(),3);var e=c();a.b.end(d)}else e=c()}catch(f){c=!0;try{mc(d),c=a.B(b,new Sb(f,{message:pc(f)}),void 0,void 0)}catch(g){a.l(217,g)}if(!c)throw f;}return e};_.sc=function(a,b,c){var d=rc;return function(e){for(var f=[],g=0;g<arguments.length;++g)f[g]=arguments[g];return qc(d,a,function(){return b.apply(c,f)})}};pc=function(a){var b=a.toString();a.name&&-1==b.indexOf(a.name)&&(b+=": "+a.name);a.message&&-1==b.indexOf(a.message)&&(b+=": "+a.message);if(a.stack){a=a.stack;try{-1==a.indexOf(b)&&(a=b+"\n"+a);for(var c;a!=c;)c=a,a=a.replace(/((https?:\/..*\/)[^\/:]*:\d+(?:.|\n)*)\2/,"$1");b=a.replace(/\n */g,"\n")}catch(d){}}return b};uc=function(){if(!dc.google_measure_js_timing){var a=nc;a.b=!1;a.events!=a.g.google_js_reporting_queue&&(jc()&&(0,_.tc)(a.events,mc),a.events.length=0)}};_.vc=function(a,b,c){fc(cc,a,b,!0,c,void 0)};_.wc=function(a,b){var c=/[?&]adurl=([^&]+)/.exec(a);if(!c||!/[?&]ae=1(&|$)/.test(a)||/[?&]dsh=1(&|$)/.test(a))return null;try{var d=b?c.index:a.length;return{Ha:a.slice(0,d)+"&act=1"+a.slice(d),M:decodeURIComponent(c[1])}}catch(e){return null}};yc=function(a){var b=_.xc(a.href),c=b.oa;Kb(a,b.ha);return c};_.xc=function(a){var b=_.wc(a,!0);return b?navigator.sendBeacon?navigator.sendBeacon(_.zc(b.Ha,"&ri=1"),"")?{ha:b.M,oa:!0}:{ha:_.zc(a,"&ri=2"),oa:!1}:{ha:_.zc(a,"&ri=16"),oa:!1}:{ha:a,oa:!1}};_.zc=function(a,b){var c=a.search(/&adurl=/);return 0>c?a+b:a.slice(0,c)+b+a.slice(c)};Ac=function(a){return null!==_.wc(a.href)||(a.getAttribute("data-orig-async-clicktrack-url")?null!==_.wc(a.getAttribute("data-orig-async-clicktrack-url")):!1)};Bc=function(a,b,c,d,e){c="&"+b+"="+c;var f=a.indexOf("&"+d+"=");c=0>f?a+c:a.substring(0,f)+c+a.substring(f);return 2E3<c.length?void 0!==e?Bc(a,b,e,d,void 0):a:c};Cc=function(a,b,c,d){b=c(d,b);if(!(b instanceof Array))return a;(0,_.tc)(b,function(e){if(2!==e.length&&3!==e.length)return a;a=Bc(a,e[0],e[1],"adurl",e[2])});return a};Ec=function(a,b,c){this.b=a;this.v=b;this.l=c;this.G=[];this.A=[];this.K={};this.g={};this.C=this.D=!1;this.B=Dc(this.b);this.J=new Promise(function(d){d(!1)});this.F=-1;a=_.eb(this.b);b=_.fb(this.b);c=ab(this.v,ib,23);this.l&&this.b&&a&&b&&_.Rb(c)&&2===Dc(this.b)&&(this.B=2,this.J=this.l.Za({url:a,id:a,I:b}))};Fc=function(a,b,c){var d=b=b.getAttribute("data-original-click-url");if(d)for(var e=0;e<a.G.length;e++)d=Cc(d,b,a.G[e],c);return d};Gc=function(a,b){b=void 0===b?Date.now():b;return b-a.F>_.G(a.b,39,0)};Hc=function(a,b){-1===b.href.indexOf("dbm/clk")&&(Ac(b)||_.H(a.b,38))&&qc(rc,446,function(){var c=Date.now(),d;if(d=Gc(a,c))if(_.H(a.b,45))if(d=b.getAttribute("data-orig-async-clicktrack-url")){d=_.xc(d);var e=d.oa;Kb(b,d.ha);d=e}else b.setAttribute("data-orig-async-clicktrack-url",b.href),d=yc(b);else d=yc(b);d&&(a.F=c)})};Ic=function(a,b,c,d){if(0!=a.A.length&&(d.preventDefault?!d.defaultPrevented:!1!==d.returnValue)){var e=1==d.which&&!d.ctrlKey&&"_blank"!=b.target&&"_new"!=b.target;e&&_.Bb(d);for(var f=[],g={},h=0;h<a.A.length;g={ta:g.ta},h++)if(g.ta=a.A[h](c),g.ta){var m=new Promise(function(l){return function(n){_.Gb(_.L,l.ta,n)}}(g));f.push(m)}c=Promise.all(f);f=new Promise(function(l){window.setTimeout(l,2E3)});e&&Promise.race([c,f]).then((0,_.t)(Ec.prototype.S,a,b,d))}};Lc=function(a,b,c){var d=ab(a.v,ib,23),e=!1;d=_.ea(d);for(var f=d.next();!f.done;f=d.next())if(f=f.value,"use_async_for_js_click_handler"===_.G(f,1,"")&&"True"===_.G(f,2,"")){e=!0;break}e&&a.l&&2===a.B?(_.Bb(c),Jc(a,b,c,a.B,a.J).then(function(g){g||Hc(a,b)})):Kc(a,b,c)||Hc(a,b)};Mc=function(a,b,c,d){a.g[d]||(a.g[d]={});a.g[d][c]||(a.g[d][c]=[]);_.K(b,d,(0,_.t)(a.R,a,b,c,d))};Kc=function(a,b,c){var d=b.href;if(a.l){var e=Date.now(),f=Gc(a,e);if(a.l.Ma(b,c,a.b,a.C,f))return f&&(a.F=e),!0}else if(_.p.googdlu&&(_.p.googdlu.tryOpenPlayStore&&_.p.googdlu.tryOpenPlayStore(c,d,_.G(a.b,15,""))||_.p.googdlu.tryOpenItunesStore&&_.p.googdlu.tryOpenItunesStore(c,d,_.G(a.b,15,""),_.H(a.b,42),_.H(a.b,43),_.G(a.v,7,""),_.G(a.v,8,""))))return!0;return _.H(a.b,31)&&_.H(a.b,30)&&_.G(a.b,28,"")&&_.p.googdlu&&_.p.googdlu.tryOpenAppUrl?(_.p.googdlu.tryOpenAppUrl(c,d,_.G(a.b,32,""),_.G(a.b,28,"")),!0):!1};Jc=function(a,b,c,d,e){if(a.l){var f=Gc(a,Date.now()),g=ab(a.v,ib,23);return a.l.ib(b,c,a.b,a.C,e,f,g,d)}return new Promise(function(h){h(!1)})};Dc=function(a){return _.H(a,31)&&_.G(a,28,"")?1:_.eb(a)&&_.fb(a)?_.H(a,44)?3:2:0};Nc=function(a){return"string"==typeof a.className?a.className:a.getAttribute&&a.getAttribute("class")||""};Oc=function(a,b){"string"==typeof a.className?a.className=b:a.setAttribute&&a.setAttribute("class",b)};Qc=function(a,b){a.classList?b=a.classList.contains(b):(a=a.classList?a.classList:Nc(a).match(/\S+/g)||[],b=0<=(0,_.xa)(a,b));return b};_.Rc=function(a,b){if(a.classList)a.classList.add(b);else if(!Qc(a,b)){var c=Nc(a);Oc(a,c+(0<c.length?" "+b:b))}};_.Tc=function(a,b){a.classList?a.classList.remove(b):Qc(a,b)&&Oc(a,Sc(a.classList?a.classList:Nc(a).match(/\S+/g)||[],function(c){return c!=b}).join(" "))};Uc=function(a){_.p.setTimeout(function(){throw a;},0)};Wc=function(){var a=_.p.MessageChannel;"undefined"===typeof a&&"undefined"!==typeof window&&window.postMessage&&window.addEventListener&&!C("Presto")&&(a=function(){var e=_.sb(document,"IFRAME");e.style.display="none";Ta(e);document.documentElement.appendChild(e);var f=e.contentWindow;e=f.document;e.open();e.write(_.Qa(Vc));e.close();var g="callImmediate"+Math.random(),h="file:"==f.location.protocol?"*":f.location.protocol+"//"+f.location.host;e=(0,_.t)(function(m){if(("*"==h||m.origin==h)&&m.data==g)this.port1.onmessage()},this);f.addEventListener("message",e,!1);this.port1={};this.port2={postMessage:function(){f.postMessage(g,h)}}});if("undefined"!==typeof a&&!C("Trident")&&!C("MSIE")){var b=new a,c={},d=c;b.port1.onmessage=function(){if(void 0!==c.next){c=c.next;var e=c.Ia;c.Ia=null;e()}};return function(e){d.next={Ia:e};d=d.next;b.port2.postMessage(0)}}return"undefined"!==typeof document&&"onreadystatechange"in _.sb(document,"SCRIPT")?function(e){var f=_.sb(document,"SCRIPT");f.onreadystatechange=function(){f.onreadystatechange=null;f.parentNode.removeChild(f);f=null;e();e=null};document.documentElement.appendChild(f)}:function(e){_.p.setTimeout(e,0)}};Xc=function(a,b){this.l=a;this.v=b;this.g=0;this.b=null};Yc=function(){this.g=this.b=null};$c=function(){var a=Zc,b=null;a.b&&(b=a.b,a.b=a.b.next,a.b||(a.g=null),b.next=null);return b};ad=function(){this.next=this.g=this.b=null};ed=function(a){bd||cd();dd||(bd(),dd=!0);Zc.add(a,void 0)};cd=function(){if(_.p.Promise&&_.p.Promise.resolve){var a=_.p.Promise.resolve(void 0);bd=function(){a.then(fd)}}else bd=function(){var b=fd;!_.ta(_.p.setImmediate)||_.p.Window&&_.p.Window.prototype&&!C("Edge")&&_.p.Window.prototype.setImmediate==_.p.setImmediate?(gd||(gd=Wc()),gd(b)):_.p.setImmediate(b)}};fd=function(){for(var a;a=$c();){try{a.b.call(a.g)}catch(c){Uc(c)}var b=hd;b.v(a);100>b.g&&(b.g++,a.next=b.b,b.b=a)}dd=!1};_.P=function(){this.v=this.v;this.l=this.l};_.id=function(a){_.P.call(this);this.C=1;this.A=[];this.B=0;this.b=[];this.g={};this.F=!!a};jd=function(a,b,c){ed(function(){a.apply(b,c)})};ld=function(a,b,c,d,e){this.B=new _.id;this.g=a;this.g[0]=[b];this.v=[];this.l=new Ec(c,d,e);this.A=d;this.b=c;b=_.eb(this.b);c=_.fb(this.b);d=ab(this.A,ib,23);if(d=e&&this.b&&_.Rb(d))d=this.b,d=2===(_.H(d,31)&&_.G(d,28,"")?1:_.eb(d)&&_.fb(d)?_.H(d,44)?3:2:0);!d&&b&&c&&e&&(e.canOpenIntents([{url:b,id:b,I:c}],(0,_.t)(this.Qa,this))||e.canOpenURLs(b,(0,_.t)(this.Qa,this)));(e=_.N(1,"common_15click_anchor"))?(a[20]=[e],kd(this,20)):(e=_.za(_.Pb(2,"common_15click_anchor")),0<e.length&&(a[20]=e,kd(this,20)))};_.md=function(a,b,c){a=a.getElementsByAdPiece(b);if(c)for(b=0;b<a.length;b++){var d=a[b].getAttribute(c);if(d)return d}return null};kd=function(a,b){if((null==_.$a(a.A,28)||!_.H(_.I(a.A,_.gb,28),12))&&a.g[b]&&a.Ba(b)){a.v.push(b);var c=a.l;a=a.g[b];for(var d=0;d<a.length;d++){var e=a[d],f=e;f.href&&f.setAttribute("data-original-click-url",f.href);Mc(c,e,b,"mousedown");Mc(c,e,b,"click")}c.K[b]=!0}};nd=function(a,b){a=a.getElementsByAdPiece(b);for(b=0;b<a.length;b++)if(!a[b].href)return!1;return!0};od=function(a){this.C=new _.id;this.A=null;this.l=[];this.b=a;this.v=[];this.B=!1;this.g=null};pd=function(a){var b=[a];b=void 0===b?[]:b;_.p.google_logging_queue||(_.p.google_logging_queue=[]);_.p.google_logging_queue.push([10,b]);a=new od(new pb(a));_.q("adSlot",a,void 0);return a};_.qd=function(){var a=_.p.adSlot;return a?a:(rc.l(536,Error("no adslot"),void 0,void 0),pd(null))};sd=function(a,b,c){ld.call(this,a,b,c,_.qd().b,_.qd().g);for(a=0;a<rd.length;a++)kd(this,rd[a])};vd=function(a,b){var c=td,d={};if(!b)return null;d[0]=[b];Mb(ud,function(e){c[e]&&(d[e]=_.za(_.Pb(2,c[e],b)))});return new sd(d,b,a)};yd=function(a,b,c){b.gqid=wd;b.qqid=xd;b.com=a;_.vc("glaurung",b,c)};zd=function(a,b){var c=_.I(b,lb,16);c&&_.H(c,12)&&_.H(b,5)&&Qb(a,{backgroundColor:"transparent",backgroundImage:"none"})};Bd=function(a,b,c){_.N(2,"app-icon-link",b)&&(td[33]="app-icon-link");var d=a.b,e=_.N(1,"adunit",b),f=_.N(1,"ads",b);if(!e||!f)return 1;var g={overflow:"hidden"};0==_.G(d,32,0)?(g.width=_.G(d,2,0)+"px",g.height=_.G(d,3,0)+"px",g.position="absolute",g.top="0",g.left="0"):(g.width="100%",g.height="100%");Qb(e,g);zd(e,d);zd(f,d);try{c(f,a)}catch(l){return _.H(d,13)&&(Ad=l),2}c=0;d=qb(d);for(e=0;e<d.length;e++){g=d[e];var h="taw"+_.G(g,2,0);f=_.N(1,h,b);if(!f)return 3;f=vd(g,f);if(!f)return 1;var m=_.L.registerAd;m?m(f,h):c=4;h=_.L.initAppPromo;_.H(g,11)&&h&&h(f,a);if(_.H(g,19)&&(g=_.$a(g,33),0<g.length))for(h=0;h<g.length;h++)m=(0,_.t)(sd.prototype.C,f,g[h]),f.l.A.push(m);a.Da(f)}return c};Cd=function(a,b,c){var d=[];d[0]=[c];d[15]=[b];(b=_.N(1,"abgc"))&&(d[27]=[b]);(b=_.N(1,"cbc"))&&(d[28]=[b]);(b=_.N(1,"cta-button-anchor"))&&(d[4]=[b]);ld.call(this,d,c,a,_.qd().b,_.qd().g);kd(this,15);b&&kd(this,4)};Dd=function(a,b){var c={};c[0]=[b];ld.call(this,c,b,a,_.qd().b,_.qd().g)};Fd=function(a,b,c){ld.call(this,a,b,c,_.qd().b,_.qd().g);for(a=0;a<Ed.length;a++)kd(this,Ed[a]);this.listen(4,"mouseover",(0,_.t)(this.H,this,0,"onhoverbg",!1));this.listen(4,"mouseout",(0,_.t)(this.H,this,0,"onhoverbg",!0))};_.aa=[];ha="function"==typeof Object.create?Object.create:function(a){function b(){}b.prototype=a;return new b};if("function"==typeof Object.setPrototypeOf)Gd=Object.setPrototypeOf;else{var Hd;a:{var Id={Ya:!0},Jd={};try{Jd.__proto__=Id;Hd=Jd.Ya;break a}catch(a){}Hd=!1}Gd=Hd?function(a,b){a.__proto__=b;if(a.__proto__!==b)throw new TypeError(a+" is not extensible");return a}:null}ia=Gd;_.la="undefined"!=typeof window&&window===this?this:"undefined"!=typeof global&&null!=global?global:this;_.ma="function"==typeof Object.defineProperties?Object.defineProperty:function(a,b,c){a!=Array.prototype&&a!=Object.prototype&&(a[b]=c.value)};na("Promise",function(a){function b(g){this.g=0;this.l=void 0;this.b=[];var h=this.v();try{g(h.resolve,h.reject)}catch(m){h.reject(m)}}function c(){this.b=null}function d(g){return g instanceof b?g:new b(function(h){h(g)})}if(a)return a;c.prototype.g=function(g){if(null==this.b){this.b=[];var h=this;this.l(function(){h.A()})}this.b.push(g)};var e=_.la.setTimeout;c.prototype.l=function(g){e(g,0)};c.prototype.A=function(){for(;this.b&&this.b.length;){var g=this.b;this.b=[];for(var h=0;h<g.length;++h){var m=g[h];g[h]=null;try{m()}catch(l){this.v(l)}}}this.b=null};c.prototype.v=function(g){this.l(function(){throw g;})};b.prototype.v=function(){function g(l){return function(n){m||(m=!0,l.call(h,n))}}var h=this,m=!1;return{resolve:g(this.G),reject:g(this.A)}};b.prototype.G=function(g){if(g===this)this.A(new TypeError("A Promise cannot resolve to itself"));else if(g instanceof b)this.J(g);else{a:switch(typeof g){case "object":var h=null!=g;break a;case "function":h=!0;break a;default:h=!1}h?this.F(g):this.B(g)}};b.prototype.F=function(g){var h=void 0;try{h=g.then}catch(m){this.A(m);return}"function"==typeof h?this.K(h,g):this.B(g)};b.prototype.A=function(g){this.C(2,g)};b.prototype.B=function(g){this.C(1,g)};b.prototype.C=function(g,h){if(0!=this.g)throw Error("Cannot settle("+g+", "+h+"): Promise already settled in state"+this.g);this.g=g;this.l=h;this.D()};b.prototype.D=function(){if(null!=this.b){for(var g=0;g<this.b.length;++g)f.g(this.b[g]);this.b=null}};var f=new c;b.prototype.J=function(g){var h=this.v();g.za(h.resolve,h.reject)};b.prototype.K=function(g,h){var m=this.v();try{g.call(h,m.resolve,m.reject)}catch(l){m.reject(l)}};b.prototype.then=function(g,h){function m(u,J){return"function"==typeof u?function(D){try{l(u(D))}catch(w){n(w)}}:J}var l,n,r=new b(function(u,J){l=u;n=J});this.za(m(g,l),m(h,n));return r};b.prototype.catch=function(g){return this.then(void 0,g)};b.prototype.za=function(g,h){function m(){switch(l.g){case 1:g(l.l);break;case 2:h(l.l);break;default:throw Error("Unexpected state: "+l.g);}}var l=this;null==this.b?f.g(m):this.b.push(m)};b.resolve=d;b.reject=function(g){return new b(function(h,m){m(g)})};b.race=function(g){return new b(function(h,m){for(var l=_.ea(g),n=l.next();!n.done;n=l.next())d(n.value).za(h,m)})};b.all=function(g){var h=_.ea(g),m=h.next();return m.done?d([]):new b(function(l,n){function r(D){return function(w){u[D]=w;J--;0==J&&l(u)}}var u=[],J=0;do u.push(void 0),J++,d(m.value).za(r(u.length-1),n),m=h.next();while(!m.done)})};return b});pa.prototype.toString=function(){return this.b};_.Kd=function(){function a(c){if(this instanceof a)throw new TypeError("Symbol is not a constructor");return new pa("jscomp_symbol_"+(c||"")+"_"+b++,c)}var b=0;return a}();_.p=this||self;Ld="closure_uid_"+(1E9*Math.random()>>>0);Md=0;_.O=Date.now||function(){return+new Date};var Sc;_.xa=Array.prototype.indexOf?function(a,b){return Array.prototype.indexOf.call(a,b,void 0)}:function(a,b){if("string"===typeof a)return"string"!==typeof b||1!=b.length?-1:a.indexOf(b,0);for(var c=0;c<a.length;c++)if(c in a&&a[c]===b)return c;return-1};_.tc=Array.prototype.forEach?function(a,b,c){Array.prototype.forEach.call(a,b,c)}:function(a,b,c){for(var d=a.length,e="string"===typeof a?a.split(""):a,f=0;f<d;f++)f in e&&b.call(c,e[f],f,a)};Sc=Array.prototype.filter?function(a,b){return Array.prototype.filter.call(a,b,void 0)}:function(a,b){for(var c=a.length,d=[],e=0,f="string"===typeof a?a.split(""):a,g=0;g<c;g++)if(g in f){var h=f[g];b.call(void 0,h,g,a)&&(d[e++]=h)}return d};_.Nd=Array.prototype.some?function(a,b){return Array.prototype.some.call(a,b,void 0)}:function(a,b){for(var c=a.length,d="string"===typeof a?a.split(""):a,e=0;e<c;e++)if(e in d&&b.call(void 0,d[e],e,a))return!0;return!1};Da.prototype.Y=!0;Da.prototype.b=function(){return this.g};var Ca={},Ba={},Sa=_.z("");var Ga;_.A.prototype.Y=!0;_.A.prototype.b=function(){return this.l.toString()};_.A.prototype.Ga=!0;_.A.prototype.g=ba(2);Ga={};_.Fa={};_.Od=String.prototype.trim?function(a){return a.trim()}:function(a){return/^[\s\xa0]*([\s\S]*?)[\s\xa0]*$/.exec(a)[1]};var La,Ja;_.B.prototype.Y=!0;_.B.prototype.b=function(){return this.l.toString()};_.B.prototype.Ga=!0;_.B.prototype.g=ba(1);La=/^(?:(?:https?|mailto|ftp):|[^:/?#]*(?:[/?#]|$))/i;Ja={};_.Ia={};var Na;a:{var Pd=_.p.navigator;if(Pd){var Qd=Pd.userAgent;if(Qd){Na=Qd;break a}}Na=""};_.Pa.prototype.Ga=!0;_.Pa.prototype.g=ba(0);_.Pa.prototype.Y=!0;_.Pa.prototype.b=function(){return this.l.toString()};var Oa={};_.Ra("<!DOCTYPE html>",0);var Vc=_.Ra("",0);_.Ra("<br>",0);_.Rd=Aa(function(){var a=document.createElement("div"),b=document.createElement("div");b.appendChild(document.createElement("div"));a.appendChild(b);b=a.firstChild.firstChild;a.innerHTML=_.Qa(Vc);return!b.parentElement});Va[" "]=_.qa;var Td,Zd;_.Sd=C("Opera");_.Nb=C("Trident")||C("MSIE");Td=C("Edge");_.Ud=C("Gecko")&&!(-1!=Na.toLowerCase().indexOf("webkit")&&!C("Edge"))&&!(C("Trident")||C("MSIE"))&&!C("Edge");_.Vd=-1!=Na.toLowerCase().indexOf("webkit")&&!C("Edge");_.Wd=C("Android");_.Xd=Ua();_.Yd=C("iPad");a:{var $d="",ae=function(){var a=Na;if(_.Ud)return/rv:([^\);]+)(\)|;)/.exec(a);if(Td)return/Edge\/([\d\.]+)/.exec(a);if(_.Nb)return/\b(?:MSIE|rv)[: ]([^\);]+)(\)|;)/.exec(a);if(_.Vd)return/WebKit\/(\S+)/.exec(a);if(_.Sd)return/(?:Version)[ \/]?(\S+)/.exec(a)}();ae&&($d=ae?ae[1]:"");if(_.Nb){var be=Xa();if(null!=be&&be>parseFloat($d)){Zd=String(be);break a}}Zd=$d}_.ce=Zd;_.de=_.p.document&&_.Nb?Xa():void 0;_.ee=Ua()||C("iPod");_.fe=C("iPad");_.ge=C("Android")&&!((C("Chrome")||C("CriOS"))&&!C("Edge")||C("Firefox")||C("FxiOS")||C("Opera")||C("Silk"));var Ya="function"==typeof Uint8Array,Za=[];_.y(_.db,_.E);var cb=[20,33];_.y(_.gb,_.E);_.y(ib,_.E);_.y(_.kb,_.E);_.y(lb,_.E);_.y(pb,_.E);var nb=[1,23];_.M=document;_.L=window;var ud;ud={Mb:0,mc:1,nc:45,oc:46,$b:48,URL:2,Fb:3,xb:4,lc:5,ec:7,Sb:8,Db:9,Ub:6,Xb:34,Nb:13,yb:14,Tb:15,Vb:16,Wb:40,ic:47,rc:29,Jb:30,kc:49,ac:17,Gb:18,Lb:19,Kb:20,gc:23,Bb:24,dc:25,cc:26,Cb:27,bc:28,qc:39,pc:31,Ib:32,Ab:33,Ob:35,Yb:36,zb:37,Hb:38,Zb:42,fc:43,hc:44,Eb:50,Pb:1E3,Qb:1001,Rb:1002};_.he=[16,47,49,18,27,28,39];_.rb.prototype.ceil=function(){this.b=Math.ceil(this.b);this.g=Math.ceil(this.g);return this};_.rb.prototype.floor=function(){this.b=Math.floor(this.b);this.g=Math.floor(this.g);return this};_.rb.prototype.round=function(){this.b=Math.round(this.b);this.g=Math.round(this.g);return this};var Cb=Aa(function(){var a=!1;try{var b=Object.defineProperty({},"passive",{get:function(){a=!0}});_.p.addEventListener("test",null,b)}catch(c){}return a});var Ib=/^((market|itms|intent|itms-appss):\/\/)/i;var ie=!!window.google_async_iframe_id,je=ie&&window.parent||window;_.Ea(_.z("//fonts.googleapis.com/css"));var ke=/^https?:\/\/(\w|-)+\.cdn\.ampproject\.(net|org)(\?|\/|$)/;var le=null;var lc=_.p.performance,me=!!(lc&&lc.mark&&lc.measure&&lc.clearMarks),jc=Aa(function(){var a;if(a=me){var b;if(null===le){le="";try{a="";try{a=_.p.top.location.hash}catch(c){a=_.p.location.hash}a&&(le=(b=a.match(/\bdeid=([\d,]+)/))?b[1]:"")}catch(c){}}b=le;a=!!b.indexOf&&0<=b.indexOf("1337")}return a});kc.prototype.start=function(a,b){if(!this.b)return null;var c=hc()||gc();a=new ic(a,b,c);b="goog_"+a.label+"_"+a.uniqueId+"_start";lc&&jc()&&lc.mark(b);return a};kc.prototype.end=function(a){if(this.b&&"number"===typeof a.value){var b=hc()||gc();a.duration=b-a.value;b="goog_"+a.label+"_"+a.uniqueId+"_end";lc&&jc()&&lc.mark(b);!this.b||2048<this.events.length||this.events.push(a)}};_.oc.prototype.pinger=ba(3);_.oc.prototype.l=function(a,b,c,d,e){e=e||"jserror";try{var f=new Vb;f.v=!0;Zb(f,1,"context",a);b.error&&b.meta&&b.id||(b=new Sb(b,{message:pc(b)}));b.msg&&Zb(f,2,"msg",b.msg.substring(0,512));var g=b.meta||{};if(this.g)try{this.g(g)}catch(x){}if(d)try{d(g)}catch(x){}b=[g];f.b.push(3);f.g[3]=b;d=_.p;b=[];g=null;do{var h=d;if(zb(h)){var m=h.location.href;g=h.document&&h.document.referrer||null}else m=g,g=null;b.push(new Ub(m||""));try{d=h.parent}catch(x){d=null}}while(d&&h!=d);m=0;for(var l=b.length-1;m<=l;++m)b[m].depth=l-m;h=_.p;if(h.location&&h.location.ancestorOrigins&&h.location.ancestorOrigins.length==b.length-1)for(l=1;l<b.length;++l){var n=b[l];n.url||(n.url=h.location.ancestorOrigins[l-1]||"",n.Na=!0)}var r=new Ub(_.p.location.href,!1);h=null;var u=b.length-1;for(n=u;0<=n;--n){var J=b[n];!h&&ke.test(J.url)&&(h=J);if(J.url&&!J.Na){r=J;break}}J=null;var D=b.length&&b[u].url;0!=r.depth&&D&&(J=b[u]);var w=new Tb(r,J);w.g&&Zb(f,4,"top",w.g.url||"");Zb(f,5,"url",w.b.url||"");fc(this.v,e,f,this.A,c)}catch(x){try{fc(this.v,e,{context:"ecmserr",rctx:a,msg:pc(x),url:w&&w.b.url},this.A,c)}catch(jb){}}return!0};var cc,rc,ne;if(ie&&!zb(je)){var oe="."+_.M.domain;try{for(;2<oe.split(".").length&&!zb(je);)_.M.domain=oe=oe.substr(oe.indexOf(".")+1),je=window.parent}catch(a){}zb(je)||(je=window)}var dc=je,nc=new kc;(function(){cc=new bc;"number"!==typeof dc.google_srt&&(dc.google_srt=Math.random());ec();rc=new _.oc;rc.g=function(b){var c=_.L.jerExpIds;if(_.sa(c)&&0!==c.length){var d=b.eid;if(d){c=fa(d.split(",")).concat(fa(c));d={};for(var e=0,f=0;f<c.length;){var g=c[f++];var h=g;h=_.ua(h)?"o"+(h[Ld]||(h[Ld]=++Md)):(typeof h).charAt(0)+h;Object.prototype.hasOwnProperty.call(d,h)||(d[h]=!0,c[e++]=g)}c.length=e;b.eid=c.join(",")}else b.eid=c.join(",")}ne&&(b.jc=ne);(c=_.L.jerUserAgent)&&(b.useragent=c)};rc.A=!0;"complete"==dc.document.readyState?uc():nc.b&&_.K(dc,"load",function(){uc()});var a=_.M.currentScript;ne=a?a.dataset.jc:""})();Ec.prototype.S=function(a,b){this.D=!0;var c=!1;b.target&&(c=_.Ob(b.target,b.button,b.ctrlKey,b.shiftKey,b.metaKey,b.altKey,new _.rb(b.x,b.y)));!a.href||c||Kc(this,a,b)||(Hc(this,a),_.L.top.location=a.href)};Ec.prototype.R=function(a,b,c,d){if(this.D)this.D=!1;else{d||(d=_.L.event);this.g[c][b].forEach(function(f){f(d)});if(a.href){var e=Fc(this,a,d.type);e&&(a.href=e)}"click"==c&&(Ic(this,a,b,d),(d.preventDefault?d.defaultPrevented:!1===d.returnValue)||Lc(this,a,d))}};var gd;Xc.prototype.get=function(){if(0<this.g){this.g--;var a=this.b;this.b=a.next;a.next=null}else a=this.l();return a};var hd=new Xc(function(){return new ad},function(a){a.reset()});Yc.prototype.add=function(a,b){var c=hd.get();c.set(a,b);this.g?this.g.next=c:this.b=c;this.g=c};ad.prototype.set=function(a,b){this.b=a;this.g=b;this.next=null};ad.prototype.reset=function(){this.next=this.g=this.b=null};var bd,dd=!1,Zc=new Yc;_.P.prototype.v=!1;_.P.prototype.Ea=ba(4);_.P.prototype.L=ba(6);_.y(_.id,_.P);_.id.prototype.subscribe=function(a,b,c){var d=this.g[a];d||(d=this.g[a]=[]);var e=this.C;this.b[e]=a;this.b[e+1]=b;this.b[e+2]=c;this.C=e+3;d.push(e);return e};_.id.prototype.G=function(a){var b=this.b[a];b&&(b=this.g[b],0!=this.B?(this.A.push(a),this.b[a+1]=_.qa):(b&&_.ya(b,a),delete this.b[a],delete this.b[a+1],delete this.b[a+2]))};_.id.prototype.D=function(a,b){var c=this.g[a];if(c){for(var d=Array(arguments.length-1),e=1,f=arguments.length;e<f;e++)d[e-1]=arguments[e];if(this.F)for(e=0;e<c.length;e++){var g=c[e];jd(this.b[g+1],this.b[g+2],d)}else{this.B++;try{for(e=0,f=c.length;e<f;e++)g=c[e],this.b[g+1].apply(this.b[g+2],d)}finally{if(this.B--,0<this.A.length&&0==this.B)for(;c=this.A.pop();)this.G(c)}}}};_.id.prototype.L=ba(5);_.k=ld.prototype;_.k.Qa=function(a,b){b=(a=_.eb(this.b))&&b?b[a]:!1;this.l.C=!!b;this.H(0,"app_installed",!b);this.H(0,"rh-ani",b)};_.k.navigationAdPieces=function(){return this.v};_.k.Ba=function(){return!0};_.k.has=function(a){return(a=this.g[a])&&0<a.length};_.k.listen=function(a,b,c){var d=this.g[a];if(d){var e=this.l;c=_.v(c,a,this);var f=("click"==b||"mousedown"==b)&&e.K[a];e.g[b]||(e.g[b]={});e.g[b][a]||(e.g[b][a]=[]);e.g[b][a].push(c);if(!f)for(a=0;a<d.length;a++)_.K(d[a],b,c)}};_.k.H=function(a,b,c){if(b){a=this.getElementsByAdPiece(a);for(var d=0;d<a.length;d++)c?_.Tc(a[d],b):_.Rc(a[d],b)}};_.k.getElementsByAdPiece=function(a){return this.g[a]?this.g[a]:[]};_.k.creativeConversionUrl=function(){return _.G(this.b,6,"")};_.k.redirectUrl=function(){return _.G(this.b,8,"")};_.k.getIndex=function(){return _.G(this.b,2,0)};_.k.listenOnObject=function(a,b){this.B.subscribe(a,b)};_.k.fireOnObject=function(a,b){this.B.D(a,b)};_.k=od.prototype;_.k.forEachAd=function(a){(0,_.tc)(this.l,a)};_.k.Da=function(a){this.l.push(a)};_.k.bb=function(a){if(a=_.N(1,a))this.A=a;if(0==this.l.length)_.p.css=null;else{for(a=0;a<this.v.length;++a)this.v[a]();this.B=!0}};_.k.listenOnObject=function(a,b){this.C.subscribe(a,b)};_.k.fireOnObject=function(a,b){this.C.D(a,b)};_.k.registerFinalizeCallback=function(a){this.B?a():this.v.push(a)};_.k.getSerializedAdSlotData=function(){return _.bb(this.b)};_.k.getAdsLength=function(){return this.l.length};_.k.getAd=function(a){return 0<=a&&a<this.l.length&&this.l[a].getIndex()==a?this.l[a]:null};_.k.getContainer=function(){return this.A};_.k.openSystemBrowser=function(a){return this.g?(this.g.openSystemBrowser(a,{useFirstPackage:!0,useRunningProcess:!0}),!0):!1};_.k.openAttribution=function(a){return this.g?(this.g.openSystemBrowser(a,{useFirstPackage:!0,useRunningProcess:!0,useCustomTabs:!0}),!0):!1};ka(sd,ld);sd.prototype.Ba=function(a){return nd(this,a)||4===a};sd.prototype.C=function(a,b){return this.Ba(b)?a:""};var rd=[1,2,3,4,8,6,40,33,36,37,38,9];var wd="UNKNOWN",xd="UNKNOWN",Ad=null,Q={},td=(Q[1]="title-link",Q[2]="url-link",Q[3]="body-link",Q[4]="button-link",Q[8]="favicon-link",Q[6]="image-link",Q[26]="price",Q[23]="reviews",Q[43]="rating-stars",Q[44]="reviews-count",Q[24]="app-store",Q[25]="promo-headline",Q[33]="app-icon",Q[16]="image-gallery",Q[40]="image-gallery-image-link",Q[36]="logo-link",Q[37]="advertiser-link",Q[38]="call-to-action-link",Q[39]="video",Q[42]="logo",Q[50]="badge-box",Q[9]="ad-background",Q);ka(Cd,ld);ka(Dd,ld);ka(Fd,ld);Fd.prototype.Ba=function(a){return nd(this,a)||4==a};var R={},pe=(R[1]="rhtitle",R[45]="rhtitleline1",R[46]="rhtitleline2",R[48]="rhlongtitle",R[3]="rhbody",R[2]="rhurl",R[4]="rhbutton",R[8]="rhfavicon",R[14]="rhaddress",R[6]="rhimage",R[34]="rhimagetemplate",R[49]="rh-scrollflow",R[16]="rhimagegallery",R[47]="rhreviewgallery",R[29]="rhviewimagegallery",R[30]="rhcloseimagegalleryview",R[31]="rhtrydemobutton",R[32]="rhclosetrydemoview",R[39]="rhvideo",R[9]="rhbackground",R[13]="rh-icore-empty",R[5]="rhsitelink",R[7]="rhradlink",R[17]="rh-multiframe",R[18]="rh-box-breadcrumbs",R[23]="rhstarratings",R[24]="rhstoreicon",R[25]="rhpromotext",R[26]="rhprice",R[27]="abgc",R[28]="cbc",R[35]="rhdemocountdowntimer",R[36]="rhlogo",R[1001]="rhoverlap-imagegallery",R[1002]="rhoverlap-trydemo",R),Ed=[1,45,46,48,2,4,5,7,8,3,9,6,14,15,34,26,24,36];od.prototype.forEachAd=od.prototype.forEachAd;od.prototype.addAd=od.prototype.Da;od.prototype.finalize=od.prototype.bb;_.q("buildAdSlot",pd,void 0);_.q("buildGlaurungAds",function(a,b,c){var d=(new Date).getTime(),e=1,f=!1;Ad=null;try{var g=a.b;f=_.H(g,13);wd=_.G(g,8,"");xd=_.G(g,7,"");e=Bd(a,b,c)}catch(h){f&&(Ad=h),e=1}a={};yd("bridge",(a.r=e,a.d=(new Date).getTime()-d,a));return e},void 0);_.q("glaurungError",function(){return Ad},void 0);_.q("glaurungBridge.log",yd,void 0);_.q("glaurungBridge.getAdPieceClassName",function(a){return td[a]},void 0);_.q("buildImageAd",function(a,b){if(0>b||b>=qb(a.b).length)a=null;else{a=qb(a.b)[b];b=_.N(1,"google_image_div");var c=_.N(1,"aw0");a=b&&c?new Cd(a,c,b):null}return a},void 0);_.q("buildRichmediaAd",function(a,b){return 0>b||b>=qb(a.b).length?null:new Dd(qb(a.b)[b],_.M.body)},void 0);_.q("buildTextAd",function(a,b){var c=a.b;if(!(0>b||b>=qb(c).length)){if(0>b||b>=qb(a.b).length)var d=null;else{d=qb(a.b)[b];var e=_.N(1,"taw"+b);if(e){var f={0:[e]},g;for(g in ud){var h=ud[g],m=pe[h];m&&(f[h]=_.za(_.Pb(2,m,e)))}d=new Fd(f,e,d)}else d=null}d&&(_.L.registerAd&&_.L.registerAd(d,"taw"+b),a.Da(d),_.H(qb(c)[b],11)&&_.L.initAppPromo&&_.L.initAppPromo(d,a))}},void 0);})(window.hydra=window.hydra||{});
