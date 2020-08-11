import {elements} from './base';
import {Fraction} from 'fractional';
//Method used to clear recipe section of HTML in order to only display one selected recipe at a time
export const clearRecipe = () => elements.recipe.innerHTML = '';

//Method formats ingredient counts into fractions
const formatCount = count  => {
    if (count){
        // count 2.5 -> 2 1/2
        // count 0.5 -> 1/2
        //Round count to 4 decimal places to count for irrational number i.e. 1/3
        const newCount = Math.round(count * 10000)/10000;
        //Destruture the elements from count by spliting the numbers before and after . and saving them into int and dec
        const [int,dec] = newCount.toString().split('.').map(el=>parseInt(el,10));
        //If there is no decimal return count
        if(!dec) return newCount;
        if(int===0){
            //If no whole number, use fractional module to convert count into fraction
            const fr = new Fraction(newCount);
            return `${fr.numerator}/${fr.denominator}`;
        }else{
            //If both whole number and decimal exist convert count-int into fraction
            const fr = new Fraction(newCount-int);
            return `${int} ${fr.numerator}/${fr.denominator}`;
        }
    }
    return '?';
};

//Method creates HTML template for each recipe ingredient
const createIngredient = ingredient => `
    <li class="recipe__item">
        <svg class="recipe__icon">
            <use href="img/icons.svg#icon-check"></use>
        </svg>
        <div class="recipe__count">${formatCount(ingredient.count)}</div>
        <div class="recipe__ingredient">
        <span class="recipe__unit">${ingredient.unit}</span>
            ${ingredient.ingredient}
        </div>
    </li>
`;
//Method is used to populate HTML file with recipe specific information
export const renderRecipe = (recipe,isLiked) => {
    //Create a markup variable of recipe HTML and replace with recipe attributes
    const markup = `
    <figure class="recipe__fig">
        <img src="${recipe.img}" alt="${recipe.title}" class="recipe__img">
        <h1 class="recipe__title">
            <span>${recipe.title}</span>
        </h1>
    </figure>

    <div class="recipe__details">
        <div class="recipe__info">
            <svg class="recipe__info-icon">
                <use href="img/icons.svg#icon-stopwatch"></use>
            </svg>
            <span class="recipe__info-data recipe__info-data--minutes">${recipe.time}</span>
            <span class="recipe__info-text"> minutes</span>
        </div>
        <div class="recipe__info">
            <svg class="recipe__info-icon">
                <use href="img/icons.svg#icon-man"></use>
            </svg>
            <span class="recipe__info-data recipe__info-data--people">${recipe.servings}</span>
            <span class="recipe__info-text"> servings</span>

            <div class="recipe__info-buttons">
                <button class="btn-tiny btn-decrease">
                    <svg>
                        <use href="img/icons.svg#icon-circle-with-minus"></use>
                    </svg>
                </button>
                <button class="btn-tiny btn-increase">
                    <svg>
                        <use href="img/icons.svg#icon-circle-with-plus"></use>
                    </svg>
                </button>
            </div>

        </div>
        <button class="recipe__love">
            <svg class="header__likes">
                <use href="img/icons.svg#icon-heart${isLiked ? '':'-outlined'}"></use>
            </svg>
        </button>
    </div>



    <div class="recipe__ingredients">
        <ul class="recipe__ingredient-list">
            ${recipe.ingredients.map(el => createIngredient(el)).join('')}
        </ul>

        <button class="btn-small recipe__btn recipe__btn--add">
            <svg class="search__icon">
                <use href="img/icons.svg#icon-shopping-cart"></use>
            </svg>
            <span>Add to shopping list</span>
        </button>
    </div>

    <div class="recipe__directions">
        <h2 class="heading-2">How to cook it</h2>
        <p class="recipe__directions-text">
            This recipe was carefully designed and tested by
            <span class="recipe__by">${recipe.author}</span>. Please check out directions at their website.
        </p>
        <a class="btn-small recipe__btn" href="${recipe.url}" target="_blank">
            <span>Directions</span>
            <svg class="search__icon">
                <use href="img/icons.svg#icon-triangle-right"></use>
            </svg>

        </a>
    </div>
`
    //Add selected recipe to HTML
    elements.recipe.insertAdjacentHTML('afterbegin',markup);
};
//Method to update HTML with new servings and updated ingredient counts
export const updateServingIngredients = recipe => {
    //Update serving on HTML
    document.querySelector('.recipe__info-data--people').textContent = recipe.servings;
    //Update ingredients
    const countElements = document.querySelectorAll('.recipe__count');
    countElements.forEach((el,i)=>{
        //console.log(recipe.ingredients[i].count);
        el.textContent = formatCount(recipe.ingredients[i].count);
    });

};