const arrow = document.querySelector('#top-arrow');

arrow.addEventListener("click", function() {

    window.scrollTo({
        behavior: 'smooth',
        top: 0,
        left: 0,
    });
})


document.addEventListener("scroll", function(event) {
    if(window.scrollY > 0)
        arrow.style.zIndex = '1';
    else
        arrow.style.zIndex = '-1';
});
