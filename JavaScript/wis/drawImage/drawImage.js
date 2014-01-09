window.addEventListener("load", windowLoaded, false);

function windowLoaded () {
	console.log("works");
	var canvas = document.getElementById("canvas_01"); 
	var context = canvas.getContext("2d");

	var image = new Image();
	var xSpeed = 3;
	var ySpeed = 4;

	image.src = "image.png";
	image.addEventListener("load", imageLoaded, false);

	function imageLoaded () {
		xp = 0;
		yp = 0;

		setInterval(drawCanvas, 100);
	}

	function drawCanvas () {
		context.clearRect(0, 0, canvas.width, canvas.height);
		context.drawImage(image, xp, yp);
		xp += xSpeed;
		yp += ySpeed;

		if (xp >= canvas.width || xp <= 0) {
			xSpeed = -xSpeed;
		} else if (yp >= canvas.height || yp <= 0) {
			ySpeed = -ySpeed;
		}
	}
}
