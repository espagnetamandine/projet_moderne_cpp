console.log("test 1");

numberToDo = 2;

const myButton = document.getElementById("buttonToAdd");
const myList = document.getElementById("listToDo");

if (myButton) {
  myButton.addEventListener("click", addElement);
}

function addElement() {
  let myNewToDo = document.getElementById("newtodo");

  if (myNewToDo.value != "") {
    numberToDo++;

    const newToDo = document.createElement("li");
    newToDo.classList.add("element");
    newToDo.innerHTML =
      `
    <input type="checkbox" name="todo` +
      numberToDo +
      `" />
    <label for="todo` +
      numberToDo +
      `">` +
      myNewToDo.value +
      `</label>  
    `;

    deleteButton = document.createElement("button");
    deleteButton.innerHTML = "Supprimer";
    deleteButton.classList.add("deleteElement");

    newToDo.appendChild(deleteButton);
    myList.appendChild(newToDo);

    deleteButton.addEventListener("click", deleteElement);

    myNewToDo.value = "";
  } else {
    alert("Il n'y a pas de texte");
  }
}

function deleteElement() {
  const divToDelete = this.parentNode;
  divToDelete.remove();
}
