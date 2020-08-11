// Global app controller

import Search from './models/Search';
import Recipe from './models/Recipe';
import List from './models/List';
import Likes from './models/Likes';
import * as searchView from './views/searchView';
import * as recipeView from './views/recipeView';
import * as listView from './views/listView';
import * as likesView from './views/likesView';
import {elements,renderLoader,clearLoader} from './views/base';


/** Global State 
 * - Search object 
 * - Current recipe object
 * - Shopping list object
 * - Liked recipes
 */
const state = {};

/** 
 * SEARCH CONTROLLER 
*/
const controlSearch = async () =>{
    //1) Get Query from view
    const query = searchView.getInput();
    if(query){
        //2) New search object and add to state
        state.search = new Search(query);
        //3) Prepare UI for results
        searchView.clearInput();
        searchView.clearResults();
        renderLoader(elements.searchRes);
        try{
            //4) Search for recipes
            await state.search.getResults();
            //5) Render results on UI
            clearLoader();
            searchView.renderResults(state.search.result);
        }catch(err){
            alert("Something wrong with the search");
            clearLoader();
        }
    }
}

/** 
 * RECIPE CONTROLLER
*/
const controlRecipe = async () =>{
    //Get ID from URL
    const id = window.location.hash.replace('#','');
    if(id){
        //Prepare UI for changes
        recipeView.clearRecipe();
        renderLoader(elements.recipe);

        //Highlight selected search item
        if(state.search) searchView.highlightSelected(id);
        //Create new recipe object
        state.recipe = new Recipe(id);
        
        try{
            //Get Recipe Data and parse ingredients
            await state.recipe.getRecipe();
            state.recipe.parseIngredients();
            // Calculate servings and time
            state.recipe.calcTime();
            state.recipe.calcServings();
            //Render recipe
            clearLoader();
            recipeView.renderRecipe(state.recipe,state.likes.isLiked(id));
        }catch(err){
            alert('Error processing recipe');
        }
    }
};


/**
 * SHOPPING LIST CONTROLLER 
 */
const controlList = () =>{
   //Create a new list IF there is not one yet
    if(!state.list) state.list = new List();

    //Add each ingredient to the list and UI
    state.recipe.ingredients.forEach(el => {
       const item = state.list.addItem(el.count,el.unit,el.ingredient);
       listView.renderItem(item);
    });
    listView.toggleListMenu(state.list.getNumItems());
}


/**
 * LIKES CONTROLLER
 */

const controlLike = () =>{
    if(!state.likes) state.likes = new Likes();
    const currentID = state.recipe.id;
    const isLiked = state.likes.isLiked(currentID)
    //User has not liked current recipe
    if(!state.likes.isLiked(currentID)){
        //Add like to the state
        const newLike = state.likes.addLike(currentID,state.recipe.title,state.recipe.author,state.recipe.img);
        //Toggle like button
        likesView.toggleLikeBtn(true);
        //Add like to list
        likesView.renderLike(newLike);
       
    }
    //User has already liked current recipe
    else{
        //Remove like form the state
        state.likes.deleteLike(currentID);
        //Toggle the like button
        likesView.toggleLikeBtn(false);
        //Remove the like from UI list
        likesView.deleteLike(currentID);
    }
    likesView.toggleLikeMenu(state.likes.getNumLikes());
}


/**
 * Event Listeners
 */

 //Event listener that allows searches to be processed. controlSearch is called whenever a search is made
elements.searchForm.addEventListener('submit',e =>{
    e.preventDefault();
    controlSearch();
});

//Event Listener that allows recipe search results to move to previous and next page
elements.searchResPages.addEventListener('click',e => {
    const btn = e.target.closest('.btn-inline');
    if(btn){
        const goToPage = parseInt(btn.dataset.goto,10);
        searchView.clearResults();
        searchView.renderResults(state.search.result,goToPage);
    }
});

//Event Listener for recipe selection. controlRecipe method is run whenever a recipe is selected (hashchange), or when the page is loaded (load)
['hashchange','load'].forEach(event => window.addEventListener(event,controlRecipe));
//window.addEventListener('hashchange',controlRecipe);

//Event Listener which handles deleting entire shopping list
elements.deleteShopping.addEventListener('click',e =>{
    const btn = e.target.closest('.btn-small');
    if(btn){
        //Delete entire items array
        state.list.deleteAllItems();
        //Delete from 
        listView.clearList();
        //Toggle Delete Button
        listView.toggleListMenu(state.list.getNumItems());
    }
});


//Event Listner which handles delete and update shopping list item events
elements.shopping.addEventListener('click',e=>{

        //Use closest method to specially find nearest id based on position click
        const id = e.target.closest('.shopping__item').dataset.itemid;

        //Handle the delete event
        if(e.target.matches('.shopping__delete, .shopping__delete *')){
        //Delete from state
            state.list.deleteItem(id);

            //Delete from UI
            listView.deleteItem(id);
            //Toggle Delete All Button
            listView.toggleListMenu(state.list.getNumItems());
        }
        //Handle count increase/decrease
        else if (e.target.matches('.shopping__count-value')){
            const val = parseFloat(e.target.value);
            state.list.updateCount(id,val);
        }

});

//Event Listener to restore recipes on page load - Used for persistent data
window.addEventListener('load',()=>{
    //create new likes and list object
    state.likes = new Likes(); 
    state.list = new List();
    //Restore likes and list items
    state.likes.readStorage();
    state.list.readStorage();
    //Toggle Liked menu button and delete shopping list button
    likesView.toggleLikeMenu(state.likes.getNumLikes());
    listView.toggleListMenu(state.list.getNumItems());
    //Render exisiting liked recipes
    state.likes.likes.forEach(like=>likesView.renderLike(like));
    state.list.items.forEach(item=>listView.renderItem(item));


});

//Event Listener which handles recipe button clicks. Handles all DOM events on recipeView
elements.recipe.addEventListener('click',e=>{
    //Event listener is called whenever button class is clicked or any child elements as well
    //Serving Decrease button is clicked
    if(e.target.matches('.btn-decrease, .btn-decrease *')){
        if(state.recipe.servings >1) {
            state.recipe.updateServings('dec');
            recipeView.updateServingIngredients(state.recipe);
        }
    }
    //Servings increase button is clicked
    else if(e.target.matches('.btn-increase, .btn-increase *')){
        state.recipe.updateServings('inc');
        recipeView.updateServingIngredients(state.recipe);
    }
    //Add to shopping list button is clicked
    else if(e.target.matches('.recipe__btn--add, .recipe__btn--add *')){
        controlList();
    }
    //Heart button is clicked
    else if (e.target.matches('.recipe__love, .recipe__love *')){
        controlLike();
    }
});






