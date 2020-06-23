let selection = document.querySelector("select");
selection.onchange = function() {
    if (selection.options[selection.selectedIndex].text === "Swimming")
    {
        alert("Correct!");
    }
    else
    {
        alert("Wrong!");
    }
}