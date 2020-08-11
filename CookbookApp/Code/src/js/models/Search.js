import axios from 'axios';
//Search class which provides search results
export default class Search{

    constructor(query){
        this.query = query;
    }
    async getResults(){
        //Try and Catch used to determine invalid entries or if query was not found
        try{
            //Using await and axios, specific query can be found in api. API returns query if object was found
            const res = await axios(`https://forkify-api.herokuapp.com/api/search?&q=${this.query}`);
            this.result = res.data.recipes;
            
        }
        catch(error){
            alert(error);
        }   
        
    }
}





