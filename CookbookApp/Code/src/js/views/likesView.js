import {elements} from './base';
import {limitRecipeTitle} from './searchView';

//Method toggles heart button 
export const toggleLikeBtn = isLiked => {
    const iconString = isLiked ? 'icon-heart' : 'icon-heart-outlined';
    //Set attribute of heart icon depending on the value of iconString
    document.querySelector('.recipe__love use').setAttribute('href',`img/icons.svg#${iconString}`);
    
    //icons.svg#icon-heart-outlined
};

//Method toggles main favorites icon
export const toggleLikeMenu = numLikes => {
    //Use CSS attributes reveal favorites icon if likes exist and hide if no recipes are liked
    elements.likesMenu.style.visibility = numLikes >0 ? 'visible' : 'hidden';
};

//Method renders favorite on likes list
export const renderLike = like => {

    const markup = `
    <li>
        <a class="likes__link" href="#${like.id}">
            <figure class="likes__fig">
                <img src="${like.img}" alt="${like.title}">
            </figure>
            <div class="likes__data">
                <h4 class="likes__name">${limitRecipeTitle(like.title)}</h4>
                <p class="likes__author">${like.author}</p>
            </div>
        </a>
    </li>
    `;
    elements.likesList.insertAdjacentHTML('beforeend',markup);
};

//Method to delete favorite from likes list
export const deleteLike = id =>{
    //Use CSS selector to select href, hashcode attribute in likes__link HTML class and select its parent element
    const el = document.querySelector(`.likes__link[href*="${id}"]`).parentElement;
    if(el) el.parentElement.removeChild(el);
}