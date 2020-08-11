import {elements} from './base';
//Method used to render items for HTML shopping list
export const renderItem = item =>{
    const markup = `
    <li class="shopping__item" data-itemid =${item.id}>
        <div class="shopping__count">
            <input type="number" value="${item.count}" step="${item.count}" min="1" class="shopping__count-value">
            <p>${item.unit}</p>
        </div>
        <p class="shopping__description">${item.ingredient}</p>
        <button class="shopping__delete btn-tiny">
            <svg>
                <use href="img/icons.svg#icon-circle-with-cross"></use>
            </svg>
        </button>
    </li>
    `;

    elements.shopping.insertAdjacentHTML('beforeend',markup);
};
//Method used to clear shopping list off of UI
export const clearList = () => elements.shopping.innerHTML = '';

//Method used to delete items from HTML shopping list
export const deleteItem = id =>{
    //Use CSS attribute selector to select item id from HTML
    const item = document.querySelector(`[data-itemid="${id}"]`);
    if(item) item.parentElement.removeChild(item);
};


//Method toggles delete shopping list button
export const toggleListMenu = numLikes => {
    //Use CSS attributes reveal favorites icon if likes exist and hide if no recipes are liked
    elements.deleteShopping.style.visibility = numLikes >0 ? 'visible' : 'hidden';
};