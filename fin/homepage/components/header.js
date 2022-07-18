class Header extends HTMLElement {
    constructor() {
        super();
    }
  
    connectedCallback() {
        this.innerHTML = `
            <nav class="top-nav">
                <ul class="top-ul">
                    <li class="top-logo"><a class="top-a top-logo" href="index.html">devon|martin</a></li>
                    <li class="top-li"><a class="top-a" href="log-in.html">Log In</a></li>
                    <li class="top-li"><a class="top-a" href="contact-me.html">Contact Me</a></li>
                    <li class="top-li"><a class="top-a" href="gallery.html">Gallery</a></li>
                    <li class="top-li"><a class="top-a" href="about-me.html">About Me</a></li>
                </ul>
            </nav>
            <nav id="side-id" class="side-nav">
                <ul class="side-ul">
                    <li class="side-li"><a class="side-a" href="about-me.html">About Me</a></li>
                    <li class="side-li"><a class="side-a" href="gallery.html">Gallery</a></li>
                    <li class="side-li"><a class="side-a" href="contact-me.html">Contact Me</a></li>
                    <li class="side-li"><a class="side-a" href="log-in.html">Log In</a></li>
                </ul>
            </nav>
            <nav class="side-topbar">
                <a class="side-logo" href="index.html">d|m</a>
                <span class="side-span" id="side-nav-button" onclick="openNav()">
                    &#9776;
                </span>
            </nav>
        `;
    }
}

customElements.define('header-component', Header);


function openNav() {
    document.getElementById("side-id").style.width = "100%";
    document.getElementById("side-nav-button").innerHTML = "&times;";
    document.getElementById("side-nav-button").setAttribute("onClick", "javascript: closeNav();");
}
  
function closeNav() {
    document.getElementById("side-id").style.width = "0";
    document.getElementById("side-nav-button").innerHTML = "&#9776;";
    document.getElementById("side-nav-button").setAttribute("onClick", "javascript: openNav();");
}

