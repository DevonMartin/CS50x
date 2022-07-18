function css() {
    document.getElementById("picwheel-header").innerHTML = "HTML";
    document.getElementById("header-png").setAttribute("src", "pictures/header-css.png");
    document.getElementById("picwheel-header").setAttribute("onclick", "html()");
}

function html() {
    document.getElementById("picwheel-header").innerHTML = "CSS";
    document.getElementById("header-png").setAttribute("src", "pictures/header-html.png");
    document.getElementById("picwheel-header").setAttribute("onclick", "css()");   
}