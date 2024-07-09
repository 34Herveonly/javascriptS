const todoList = [
  {
    name: 'Earn money',
    dueDate: '2023-12-15'
  },
  {
    name: 'develop yourself',
    dueDate: '2023-12-14'
  }
];
renderTodoList();

function renderTodoList() {
  let todoListHTML = '';

  todoList.forEach(function(todoObject,index ){
     {
      let todoObject = todoList[i];
      const { name, dueDate } = todoObject;
      const html = `
  <div>
  ${name} </div>
      <div>${dueDate}</div>
      <button onclick="todoList.splice(${index}, 1); renderTodoList();" class="delete-todo-button">Delete</button>`;
  
      todoListHTML += html;
    }
    document.querySelector('.js-todo-list').innerHTML = todoListHTML;
  })
  
}
function addTodo() {
  const inputElement = document.querySelector('.js-name-input');
  const name = inputElement.value;

  const dateInputElement = document.querySelector('.js-due-date-input');
  const dueDate = dateInputElement.value;

  todoList.push({ name, dueDate }); // Corrected to use dueDate (with lowercase 'd')
  console.log(todoList);

  inputElement.value = '';
  dateInputElement.value = ''; // Clear the date input
  renderTodoList();
}


function control(event) {
  if (event.key === 'Enter') {
    addTodo();
  }
}