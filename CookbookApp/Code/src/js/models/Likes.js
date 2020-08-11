
//Likes class that represents all liked recipes
export default class Likes {
    constructor(){
        this.likes = [];
    }

    //Method adds recipe to favorites
    addLike(id,title,author,img){
        const like = {
            id,
            title,
            author,
            img
        }
        this.likes.push(like);
        //Persist data in localStorage
        this.persistData();
        return like; 
    }
    //Method deletes recipe from favorites
    deleteLike(id){
        //Find the positon of the item that matches id
        const index = this.likes.findIndex(el => el.id===id);
        //[2,4,8] splice(1,1) return 4, original array is [2,8]
        //[2,4,8] slice(1,1) return 4, original array is [2,4,8]
        this.likes.splice(index,1) // item[index] is removed

        //Persist data in localStorage
        this.persistData();
    }
    //Method determines which recipe is liked
    isLiked(id){
        //Returns true if recipe is liked, else returns false
        return this.likes.findIndex(el => el.id ===id) !== -1;
    }
    //Method returns length of likes array
    getNumLikes(){
        return this.likes.length;
    }
    //Method to store likes ot local storage
    persistData(){
        localStorage.setItem('likes',JSON.stringify(this.likes));
    }
    //Method to restore likes to local storage
    readStorage(){
        const storage = JSON.parse(localStorage.getItem('likes'));
        //Restoring likes from localStorage
        if(storage) this.likes = storage;
    }
}