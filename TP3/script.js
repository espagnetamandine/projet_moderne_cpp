console.log("test 1");

numberToDo = 2;

const myButton = document.getElementById("buttonToAdd");
const myList = document.getElementById("listToDo");

if (myButton) {
  myButton.addEventListener("click", addElement);
}

function addElement() {
  let myNewToDo = document.getElementById("newtodo").value;

  if (myNewToDo != "") {
    console.log(myNewToDo);
    console.log(numberToDo);
    numberToDo++;

    const newToDo = document.createElement("div");
    newToDo.classList.add("element");
    newToDo.innerHTML =
      `
    <input type="checkbox" id=="todo` +
      numberToDo +
      `" name=="todo` +
      numberToDo +
      `" />
    <label for="todo` +
      numberToDo +
      `">` +
      myNewToDo +
      `</label>
      
    `;

    deleteButton = document.createElement("button");
    deleteButton.innerHTML = "Supprimer";
    deleteButton.classList.add("deleteElement");

    newToDo.appendChild(deleteButton);
    myList.appendChild(newToDo);

    deleteButton.addEventListener("click", function (e) {
      const divToDelete = this.parentNode;
      divToDelete.remove();
    });
  } else {
  }
}

function deleteElement(element) {
  const divToDelete = element.parentNode;
  divToDelete.remove();
}
