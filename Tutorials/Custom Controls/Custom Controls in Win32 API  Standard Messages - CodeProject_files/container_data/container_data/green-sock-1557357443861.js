var tl = TweenLite;

var xhr;
if (window.XMLHttpRequest) xhr = new XMLHttpRequest(); // all browsers except IE
else xhr = new ActiveXObject("Microsoft.XMLHTTP"); // for IE
xhr.open('GET', 'https://cdn.revjet.com/s3/csp/1547594878488/lt-generator.xml');
xhr.onreadystatechange = function () {
	if (xhr.readyState===4 && xhr.status===200) {
		// update HTML content
		text2.innerHTML = String(xhr.responseXML.getElementsByTagName('apr')[1].firstChild.nodeValue).substring(0,5);
	}
}
xhr.send();

// intro animations
// first run
tl.to(banner, 0.5, { opacity: 1, ease: Power0.easeNone });
tl.to(text1, 1, { left: 0, opacity: 1, ease: Power4.easeOut, delay: 0.2 });
tl.to(text2, 1, { left: 0, opacity: 1, ease: Power4.easeOut, delay: 0.2 });
tl.to(text3, 1, { left: 0, opacity: 1, ease: Power4.easeOut, delay: 0.2 });
tl.to(note, 0.8, { opacity: 1, ease: Power0.easeNone, delay: 1.3 });
tl.to(sliderlabel, 0.8, { opacity: 1, ease: Power0.easeNone, delay: 0.6 });
tl.to(slider, 0.8, { opacity: 1, ease: Power0.easeNone, delay: 0.6 });
tl.to(slideroutput, 0.8, { opacity: 1, ease: Power0.easeNone, delay: 0.6 });
tl.to(cta, 0.4, { opacity: 1, bottom: 12, ease: Back.easeOut, delay: 1.1 });
tl.to(ctatext, 0.55, { opacity: 1, left:0, ease: Power4.easeOut, delay: 1.1 });
tl.to(cta, 0.05, { height:40, ease:Power0.easeNone, delay:2 });
tl.to(ctatopbg, 0.05, { backgroundColor:'#44ace6', ease:Power0.easeNone, delay:2 });
tl.to(cta, 0.05, { height:37, ease:Power0.easeNone, delay:3.2 });
tl.to(ctatopbg, 0.05, { backgroundColor:'#2f86d4', ease:Power0.easeNone, delay:3.2 });
tl.to(shine, 0.8, { left: 220, ease: Power0.easeNone, delay: 2.3 });
tl.set(shine, { left: -220, delay: 5.6 });

// second run
tl.to(text1, 0.8, { left: -300, opacity: 0, ease: Power4.easeIn, delay: 5.4 });
tl.to(text2, 0.8, { left: 300, opacity: 0, ease: Power4.easeIn, delay: 5.4 });
tl.to(text3, 0.8, { left: -300, opacity: 0, ease: Power4.easeIn, delay: 5.4 });
tl.set(text1, { left: 300, delay: 6.5 });
tl.set(text2, { left: -300, delay: 6.5 });
tl.set(text3, { left: 300, delay: 6.5 });
tl.to(text1, 1, { left: 0, opacity: 1, ease: Power4.easeOut, delay: 6.6 });
tl.to(text2, 1, { left: 0, opacity: 1, ease: Power4.easeOut, delay: 6.6 });
tl.to(text3, 1, { left: 0, opacity: 1, ease: Power4.easeOut, delay: 6.6 });
tl.to(shine, 0.8, { left: 220, ease: Power0.easeNone, delay: 7.4 });
tl.set(shine, { left: -220, delay: 8.2 });

// third run
tl.to(text1, 0.8, { left: -300, opacity: 0, ease: Power4.easeIn, delay: 11.4 });
tl.to(text2, 0.8, { left: 300, opacity: 0, ease: Power4.easeIn, delay: 11.4 });
tl.to(text3, 0.8, { left: -300, opacity: 0, ease: Power4.easeIn, delay: 11.4 });
tl.set(text1, { left: 300, delay: 12.5 });
tl.set(text2, { left: -300, delay: 12.5 });
tl.set(text3, { left: 300, delay: 12.5 });
tl.to(text1, 1, { left: 0, opacity: 1, ease: Power4.easeOut, delay: 12.6 });
tl.to(text2, 1, { left: 0, opacity: 1, ease: Power4.easeOut, delay: 12.6 });
tl.to(text3, 1, { left: 0, opacity: 1, ease: Power4.easeOut, delay: 12.6 });
tl.to(shine, 0.8, { left: 220, ease: Power0.easeNone, delay: 13.4 });

// main hit clickTAG functions
function hitClick() {
	var separator = clickTag.indexOf('?') > -1 ? '&' : '?';
	revjet.elements.runAction({
    "type": "link",
    "sourceWidgetId": sourceWidgetId,
    "url": clickTAG  + separator + 'desired-loan-amount=' + cash + '&estproperty-value=' + cash + '&purchase-price=' + cash + '&amount=' + cash,
    "target": "_blank"
});	
}

function hitOver() {
    tl.to(ctatopbg, 0.05, { backgroundColor:'#44ace6', ease:Power0.easeNone });
    tl.to(cta, 0.05, { height:40, ease:Power0.easeNone });
}

function hitOut() {
    tl.to(ctatopbg, 0.05, { backgroundColor:'#2f86d4', ease:Power0.easeNone });
    tl.to(cta, 0.05, { height:37, ease:Power0.easeNone });
}

hit.addEventListener('mouseover', hitOver, false);
hit.addEventListener('mouseout', hitOut, false);
hit.addEventListener('click', hitClick, false);

// slider features
var dragging = false;
var drag_x;
var sliderval = 0;
var maxval = 250;
var cash;
var MOUSE = 0;
var TOUCH = 1;

function setCash(value) {
	var pvalue = Math.round(Math.floor(value * 995 + 5) / 5) * 5 + '000';
	var formatted = '';
	var i = pvalue.length;
	var c = 0;
	while (i--) {
		formatted += pvalue[i];
		c++;
		if (i > 0 && c === 3) {
			formatted += ',';
			c = 0;
		}
	}
	var pstr = formatted.split('').reverse().join('');
	slideroutput.innerHTML = '$' + pstr;
	cash = pvalue;
}

function setSliderPos(value) {
	sliderval = value;
    tl.set(pivot, { x:value });
	sliderfill.style.width = value + 'px';
	setCash(value / maxval);
}

function updateSliderPos(event_x) {
	var new_x = event_x - sliderhit.getBoundingClientRect().left;
	new_x -= 9;
	new_x = Math.min(Math.max(0, new_x), maxval);
	setSliderPos(new_x);
}

function sliderMDown(e, agent) {
	var ex = (agent === TOUCH) ? e.changedTouches[0] : e;
	if (agent === MOUSE) {
		var button = e.which || e.button;
		if (button !== 1)
			return;
	}
	else if (e.preventDefault) {
		e.preventDefault();
	}
	if (sliderAnim) {
		sliderAnim.kill();
		sliderAnim = null;
	}
	dragging = true;
	updateSliderPos(ex.clientX);
}

function sliderMMove(e, agent) {
	var ex = (agent === TOUCH) ? e.changedTouches[0] : e;
	if (dragging) {
		updateSliderPos(ex.clientX);
	}
}

function sliderMUp(e, agent) {
	if (agent === MOUSE) {
		var button = e.which || e.button;
		if (button !== 1) {
			return;
		}
	}
	if (dragging) {
		dragging = false;
	}
}

function sliderMOver(e) {
	pivotbg.style.opacity = 0;
	pivotbgover.style.opacity = 1;
}

function sliderMOut(e) {
	pivotbg.style.opacity = 1;
	pivotbgover.style.opacity = 0;
}

sliderhit.addEventListener('mouseover', sliderMOver, false);
sliderhit.addEventListener('mouseout', sliderMOut, false);
sliderhit.addEventListener('mousedown', function(e) { sliderMDown(e, MOUSE); }, false);
sliderhit.addEventListener('touchstart', function(e) { sliderMDown(e, TOUCH); }, false);
window.addEventListener('mousemove', function(e) { sliderMMove(e, MOUSE); }, false);
window.addEventListener('touchmove', function(e) { sliderMMove(e, TOUCH); }, false);
window.addEventListener('mouseup', function(e) { sliderMUp(e, MOUSE); }, false);
window.addEventListener('touchend', function(e) { sliderMUp(e, TOUCH); }, false);

// slider animation
var pos = [0];
var sliderAnim;
setSliderPos(0);
sliderAnim = tl.to(pos, 2.5, { 0: maxval / 4.5, ease: Back.easeOut, onUpdate: function() {
	setSliderPos(pos[0]);
}, delay: 0.6 });


