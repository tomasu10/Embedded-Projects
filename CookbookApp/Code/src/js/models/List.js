import uniqid from 'uniqid';

export default class List {
//Shopping List class that represents all items in shopping list
    constructor(){
        this.items = [];
    }
    //Method adds item to shopping list
    addItem(count,unit,ingredient){
        //Create item object
        const item = {
            // Create a unique Id for the item using imported uniqid() library
            id: uniqid(),
            count,
            unit,
            ingredient
        }
        this.items.push(item);
        this.persistData();
        return item;
    }
    //Method deletes item from shopping list
    deleteItem(id){
        //Find the positon of the item that matches id
        const index = this.items.findIndex(el => el.id===id);
        //[2,4,8] splice(1,1) return 4, original array is [2,8]
        //[2,4,8] slice(1,1) return 4, original array is [2,4,8]
        this.items.splice(index,1) // item[index] is removed
        this.persistData();
    }
    //Method deletes all items from shopping List
    deleteAllItems(){
        this.items = [];
        this.persistData();
    }
    //Updates item quantity
    updateCount(id,newCount){
        //find the item object based on id using find method. Change count to newCount
        this.items.find(el => el.id ===id).count =newCount;
        this.persistData();
    }

     //Method returns length of list array
     getNumItems(){
        return this.items.length;
    }
    //Method to save Data to Local Storage
    persistData(){
        localStorage.setItem('list',JSON.stringify(this.items));
    }
    //Method to restore shopping list items from local storage
    readStorage(){
        const storage = JSON.parse(localStorage.getItem('list'));
        //Restoring likes from localStorage
        if(storage) this.items = storage;
    }
}