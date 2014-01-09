window.addEventListener("load", windowLoaded, false);

function windowLoaded () {
	console.log("works");
	var canvas = document.getElementById("canvas_01");
	var context = canvas.getContext("2d");

	var animate = new Image();
	var imageWidth, imageHeight, colLength = 6, rowHeight = 6;
	var sx, sy, sw, sh, xp, yp;
	var i = 0;

	animate.src = "sprite.png";
	animate.addEventListener("load", imageLoaded, false);

	function imageLoaded () {
		imageWidth = animate.width;
		imageHeight = animate.height;
		sw = imageWidth / 8;
		sh = imageHeight / 7;
		console.log(imageWidth, imageHeight, sw, sh);

		setInterval(drawCanvas, 100);
	}

	function drawCanvas () {
		sx = i % rowHeight * sw;
		sy = Math.floor(i / rowHeight) * sh;

		context.clearRect(0, 0, canvas.width, canvas.height);
		context.drawImage(animate, sx, sy, sw, sh, i, 0, 2 * sw, 2 * sh);

		i++;
		if (i > 22) i = 0;
	}
}
