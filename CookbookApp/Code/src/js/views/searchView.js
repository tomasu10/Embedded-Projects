import {elements} from './base';
//Method used to get value of search bar
export const getInput = () => elements.searchInput.value;
//Method used to clear value of search bar
export const clearInput = () =>{
    elements.searchInput.value = '';
};
//Method used to clear search buttons (results pages) and results list
export const clearResults = () => {
    elements.searchResList.innerHTML = '';
    elements.searchResPages.innerHTML = '';
};

//Method used to highlight selected recipe in search results
export const highlightSelected = id =>{
    //Create array of all objects in .results__link class
    const resultsArr = Array.from(document.querySelectorAll('.results__link'));
    //Remove highlight from all recipes
    resultsArr.forEach(el =>{
        el.classList.remove('results__link--active');
    });
    //Use CSS selector to select href, hashcode attribute in .results__link HTML class and set it to active to highlight selected recipe
    document.querySelector(`a[href*="${id}"]`).classList.add('results__link--active');
};

/* limitRecipeTitle Example
'Pasta with tomato sauce' limit = 17
acc: 0 acc + cur.length =5 / newTitle = ['Pasta']
acc: 5 acc+cur.length = 9 / newTitle = ['Pasta,'with']
acc: 9 acc+cur.length = 15 / newTitle = ['Pasta,'with','tomato']
acc: 15 acc+cur.length = 20 / newTitle = ['Pasta,'with','tomato']
*/
//Method limits the length of recipe title in order to provide more elegant results list
 export const limitRecipeTitle = (title,limit=17) => {
    const newTitle = [];
    //Split title string into an array
    const titles = title.split(' ');
    if(title.length > limit){
        //Use reduce function to eliminate all elements that do not meet criteria below
        titles.reduce((acc,cur)=> {
            //acc = running total of length of title, curr = current array element
            //Check to see if first element is greater than limit OR if the total limit has not be reached
            if((acc ===0 && cur.length>= limit) || (acc + cur.length <= limit)){
                newTitle.push(cur);
            }
            
            return acc + cur.length;
        },0);
        return `${newTitle.join(' ')}...`; 
    }

    return title;
}

//Method allows recipes to be rendered in HTML results list
const renderRecipe = recipe => {
    const markup = `
    <li>
                    <a class="results__link" href="#${recipe.recipe_id}">
                        <figure class="results__fig">
                            <img src="${recipe.image_url}" alt="Test">
                        </figure>
                        <div class="results__data">
                            <h4 class="results__name">${limitRecipeTitle(recipe.title)}</h4>
                            <p class="results__author">${recipe.publisher}</p>
                        </div>
                    </a>
                </li>
    `;
    elements.searchResList.insertAdjacentHTML('beforeend',markup);
};

//Type: 'prev' or 'next'
//Method creates search buttons depending on type and page
const createButton = (page,type) =>
//If type is 'prev button' goto page is page -1 and button # is page -1, else page +1
//If type is 'prev' button emblem (triangle) points to the left, else right 
 `
    <button class="btn-inline results__btn--${type}" data-goto=${type === 'prev'?page-1:page+1}>
        <span>Page ${type === 'prev'?page-1:page+1}</span>
        <svg class="search__icon">
            <use href="img/icons.svg#icon-triangle-${type === 'prev'?'left':'right'}"></use>
        </svg>
    </button>           
`;

//Method allows buttons to be rendered on HTML
const renderButtons = (page,numResults,resPerPage) =>{
    //Determine how many pages there will be based on number of recipes and desired recipes per page
    const pages = Math.ceil(numResults/resPerPage);
    let button;
    if(page ===1&&pages>1){
        //Button to go to next page
       button = createButton(page,'next');
    }
    else if (page<pages){
        //Both Buttons
        button = `
            ${createButton(page,'prev')}
            ${createButton(page,'next')};
        `;
    }
    else if (page === pages && pages >1){
        //Button to go to previous page
        button = createButton(page,'prev');
    }
    //Add to HTML
    elements.searchResPages.insertAdjacentHTML('afterbegin',button);

};
//Method creates recipes for each results page
/*
Ex. page =1 resPerPage = 0
start = (1-1)*10=0
end = 1*10=10
There when the first page is selected, recipes 0-9 will be displayed

*/
export const renderResults = (recipes,page=1,resPerPage =10) => {
    //render results of current page
    const start = (page-1) * resPerPage;
    const end = page * resPerPage;
    recipes.slice(start,end).forEach(renderRecipe);

    //render page buttons
    renderButtons(page,recipes.length,resPerPage);


};