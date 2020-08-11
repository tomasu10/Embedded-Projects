import axios from 'axios';
//Recipe class which provides recipe information
export default class Recipe{
    constructor(id){
        this.id = id;
    }

    async getRecipe(){
        //Try and Catch used to determine invalid entries or if id was not found
        try{
            //Using await and axios, specific id can be found in api. API returns recipe id if found
            const res = await axios(`https://forkify-api.herokuapp.com/api/get?rId=${this.id}`);
            this.title = res.data.recipe.title;
            this.author = res.data.recipe.publisher;
            this.img = res.data.recipe.image_url;
            this.url = res.data.recipe.source_url;
            this.ingredients = res.data.recipe.ingredients;
        }catch(error){
            alert(error);
        }
    }
    //Method calculate time needed to make recipe. Estimate 15 mins per every 3 ingredients
    calcTime(){
        const numIng = this.ingredients.length;
        const periods = Math.ceil(numIng/3);
        this.time = periods *15;
    }
    //Method calcualtes servings 
    calcServings () {
        this.servings = 4;
    }
    //Method intended to receive all ingredients from the API with identical formats
    parseIngredients(){
        //Create Arrays that will be used identify long unit descriptions (unitsLong) and change them to abbreviations (unitsShort)
        const unitsLong = ['tablespoons','tablespoon','ounces','ounce','teaspoons','teaspoon','cups','pounds'];
        const unitsShort = ['tbsp','tbsp','oz','oz','tsp','tsp','cup','pound'];
        const units = [...unitsShort,'kg','g'];
        const newIngredients = this.ingredients.map(el =>{
            //1)Uniform units
            let ingredient = el.toLowerCase();
            //Identify if ingredient is in unitsLong. If Yes replace with corresponding string in unitsShort
            unitsLong.forEach((unit,i)=>{
                ingredient = ingredient.replace(unit,unitsShort[i]);
            });
            //2)Remove parenthesis
            //Use regular expression to remove parenthesis
            ingredient = ingredient.replace(/ *\([^)]*\) */g, ' ');
            //3)Parse ingredients into count, unit and ingredients
            //Split ingredient string by spaces
            const arrIng = ingredient.split(' ');
            //Use findIndex method to see what unit is used in ingredient
            const unitIndex = arrIng.findIndex(el2 => units.includes(el2));
            let objIng;
            if(unitIndex > -1){
                //There is a unit
                //Ex. 4 1/2 cups, arrCount [4,1/2] --> eval("4+1/2") = 4.5
                //Ex. 4 cups, arrCount [4]
                const arrCount = arrIng.slice(0,unitIndex);
                let count;
                //If there is only one number count can be set as the first element of arrIng
                if(arrCount.length ===1){
                    //If arrIng[0] contains a - (1-1/2), replace it with a + and evaluate the result
                    count = eval(arrIng[0].replace('-','+'));
                }else{ // Else use eval method to evaluate the addition between the first and second element in arrIng
                    count = eval(arrIng.slice(0,unitIndex).join('+'));
                }

                objIng = {
                    count: count,
                    unit: arrIng[unitIndex],
                    ingredient: arrIng.slice(unitIndex+1).join(' ')
                };
            }else if(parseInt(arrIng[0],10)){
                //No unit but first element is a number
                objIng = {
                    count: parseInt(arrIng[0],10),
                    unit: '',
                    ingredient: arrIng.slice(1).join(' ')
                };
            } else if (unitIndex ===-1){
                //No unit and no number in first element
                objIng = {
                    count: 1,
                    unit: '',
                    ingredient
                };
            }
            return objIng;
        });
        this.ingredients = newIngredients;
    }
    //Method updates servings size based on users selection
    updateServings(type){
        //Servings
        const newServings = type === 'dec' ? this.servings -1:this.servings+1;
        //Ingredients
        this.ingredients.forEach(ing => {
            //Ensures that ingredients are updated proportionately
            ing.count = ing.count * (newServings/this.servings);
        });

        this.servings = newServings;
    }
}