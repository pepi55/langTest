//JavaScript Document

window.addEventListener("load", windowLoaded, false);

function windowLoaded () {
	var canvas = document.getElementById("canvas_01");
	var context = canvas.getContext("2d");

	context.fillStyle = "red";
	context.strokeStyle = "blue";

	context.fillRect(10, 10, 50, 20);
	context.strokeRect(100, 100, 130, 100);

	context.beginPath();

	context.moveTo(100, 100);
	context.lineTo(165, 50);
	context.lineTo(230, 100);
	context.lineTo(100, 100);

	context.lineWidth = 2;

	context.stroke();
}
