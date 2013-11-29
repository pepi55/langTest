window.addEventListener("load", widnowLoaded, false);

function windowLoaded() {
	var feedback = document.getElementById("feedback");

	feedback.innerHTML = "";

	for (var i = 1; i <= 1000; i++) {
		feedback.innerHTML += i + "," + delers(i).length + ":" + delers(i) + "<br />";
	}
}
