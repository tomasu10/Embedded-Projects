//Data Module
var budgetController = (function(){
	var Expense = function(id,description,value){
		this.id = id,
		this.description = description,
		this.value = value
		this.percentage = -1;
	};
	Expense.prototype.calcPercentages = function(totalIncome){
		if(totalIncome>0){
			this.percentage = Math.round((this.value/totalIncome)*100);
		}else{
			this.percentage =-1;
		}
	};
	
	Expense.prototype.getPercentages = function(){
		return this.percentage;
	};
	var Income  = function(id,description,value){
		this.id = id,
		this.description = description,
		this.value = value
	};
	
	var calculateTotal = function(type){
		var sum =0;
		data.allItems[type].forEach(function(current){
			sum += current.value;
		});
		
		data.totals[type] = sum;
	};
	
	function compare(comp1,comp2){
	
		 
		 var comparison = 0;
		 if(comp1 >comp2) comparison =1;
		 else if (comp1<comp2) comparison =-1;
		 
		 return comparison*-1;
	}
	
	 
	var data = {
		allItems: {
			exp: [],
			inc: []
		},
		totals: {
			exp: 0,
			inc: 0
		},
		budget: 0,
		percentage: -1
	 };
	 return {
		 addItem : function(type,des,val){
			 var newItem,ID;
			 //ID = Value of last index in 'type' array in allItems object
			 if(data.allItems[type].length>0){
				ID = data.allItems[type][data.allItems[type].length-1].id+1 ;
				console.log(data.allItems[type].length);
			 }else{
				 ID =0;
			 }
			 //Create new itme based on 'exp' or 'inc' type
			 if(type === 'exp'){
				 newItem = new Expense(ID,des,val);
			 }else if (type === 'inc'){
				 newItem = new Income(ID,des,val);
			 }
			 //Push newItem into respective array based on type
			 data.allItems[type].push(newItem);
			 
			 //var valArr = data.allItems[type]
			 //Return item
			 console.log(data.allItems[type]);
			 var tempMyObj = data.allItems[type].slice();
			 return tempMyObj;
		 },
		 deleteItem: function(type,id){
			 var ids,index;
			 
			 //.map returns an array of all IDs in Inc or Exp 
			 ids = data.allItems[type].map(function(current){
				 return current.id;
			 });
			//Get index of id in INC or EXP arrays
			 index = ids.indexOf(id);
			 if(index !== -1){
				 //.splice method removes 1 item with the given index
				 data.allItems[type].splice(index,1);
			 }
			 return data.allItems[type];
			 
		 },
		 calculateBudget: function(){
			 // Calculate total income and expenses
			 calculateTotal('exp');
			 calculateTotal('inc');
			 //Calculate the budget: income - expenses
			 data.budget = data.totals.inc - data.totals.exp;
			 //Calculate percentage of expenses to income
			 if(data.totals.inc >0){
				data.percentage = Math.round((data.totals.exp / data.totals.inc)*100);
			 }else{
				data.percentage = -1;
			 }
	
		 },
		 getBudget: function(){
			 return {
				budget: data.budget,
				totalInc: data.totals.inc,
				totalExp: data.totals.exp,
				percentage: data.percentage
			 };
		 },
		 calculatePercentages: function(){
			 data.allItems['exp'].forEach(function(current){
				 current.calcPercentages(data.totals['inc']);
			 });
		 },
		 getPercentages: function(){
			 //Use .map to store all percentages in an array
			 
			 var allPercentages = data.allItems['exp'].map(function(current){
				 return current.getPercentages();
			 });
			 //Sort Percentages in descending order  to match the list items
			 //Use private budgetController compare method to sort percentages in descending order
			 allPercentages.sort(compare);
			 return allPercentages;
		 },
		 testing : function(){
			 console.log(data);
		 }
	 };
})();


//UI Module
var UIController = (function(){
	//DOM classes used in HTML
	var DOMstrings = {
		inputType: '.add__type',
		inputDescription : '.add__description',
		inputValue : '.add__value',
		inputBtn : '.add__btn',
		incomeContainer : '.income__list',
		expensesContainer : '.expenses__list',
		budgetLabel: '.budget__value',
		incomeLabel: '.budget__income--value',
		expensesLabel: '.budget__expenses--value', 
		percentageLabel: '.budget__expenses--percentage',
		container: '.container',
		expensesPercLabel: '.item__percentage',
		dateLabel: '.budget__title--month'
		
	};
	var formatNumber = function(num,type){
		/*
		+ or - number
		exactly 2 decimal point
		comma separating the thousands
		*/
		var numSplit,int,dec;
		num = Math.abs(num);
		//Fix to 2 decimals
		num = num.toFixed(2);
		//Split integer and decimals
		numSplit = num.split('.');
		int = numSplit[0];
		if(int.length>3){
			int = int.substr(0,int.length-3)+','+int.substr(int.length-3,int.length);
		}
		dec = numSplit[1];
		
		type === 'exp' ? sign = '-': sign = '+';
		
		return (type === 'exp' ? '-': '+') + ' ' + int + '.'+ dec;
	}	
	
	var nodeListForEach = function(list,callback){
		for(var i =0;i<list.length;i++){
			//Loops through each item in fields and calls callback function (Allows each expense percentage to be processed)
			callback(list[i],i);
		}
	};
	
	function compare(comp1,comp2){
		 var value1 = comp1.value;
		 var value2 = comp2.value;
		 
		 var comparison = 0;
		 if(value1 >value2) comparison =1;
		 else if (value1<value2) comparison =-1;
		 
		 return comparison*-1;
	 }
	
	return {
		getInput: function(){
			return{
				type: document.querySelector(DOMstrings.inputType).value, // inc or exp
				description: document.querySelector(DOMstrings.inputDescription).value,
				value: parseFloat(document.querySelector(DOMstrings.inputValue).value)
			};
		},
		getDOMstrings : function (){
			return DOMstrings;
		},
		addListItem : function(obj,type){
			var HTML,newHTML,element;
			//Create HTML String with placeholder text
			if(type === 'inc'){
				element = DOMstrings.incomeContainer;
				HTML ='<div class="item clearfix" id="inc-%id%"><div class="item__description">%description%</div> <div class="right clearfix"><div class="item__value">%value%</div> <div class="item__delete"><button class="item__delete--btn"><i class="ion-ios-close-outline"></i></button></div></div></div>'
			}else if(type === 'exp'){
				element = DOMstrings.expensesContainer;
				HTML ='<div class="item clearfix" id="exp-%id%"><div class="item__description">%description%</div><div class="right clearfix"><div class="item__value">%value%</div><div class="item__percentage">21%</div><div class="item__delete"><button class="item__delete--btn"><i class="ion-ios-close-outline"></i></button></div></div></div>'
			}
			//delete all line items in order to resort using array of either type 'inc' or 'exp'
			for(var i= 0;i<obj.length-1;i++){
				this.deleteListItem(type + '-' +obj[i].id);
			}
			//Sort 'inc' or 'exp' array by value and loop through it in order to addListItems sorted by value
			//Use private UIController compare method to sort arrays in descending order based on the objects value
			var sortedObj = obj.sort(compare);	
			sortedObj.forEach(function(current){
				//Replace placeholder text with data
				newHTML = HTML.replace('%id%',current.id);
				newHTML = newHTML.replace('%description%',current.description);
				newHTML = newHTML.replace('%value%',formatNumber(current.value,type));
				//Update UI
				document.querySelector(element).insertAdjacentHTML('beforeend',newHTML);
			});
			
			
		},
		deleteListItem: function(selectorID){
			var element = document.getElementById(selectorID);
			//Remove ID by accessing parent and then using remove child method
			element.parentNode.removeChild(element);
		},
		clearFields : function(){
			var fields,fieldsArr;
			//Use querySelectorAll to save values of description and value in a list
			fields = document.querySelectorAll(DOMstrings.inputDescription + ',' + DOMstrings.inputValue);
			//Convert fields from list to array usign call method
			fieldsArr = Array.prototype.slice.call(fields);
			//FieldArr holds the HTML classes for description(index=0) and value(index=1). Use the HTML function .value to obtain the information in each respective class
			fieldsArr.forEach(function(current,index,array){
				current.value = "";
				
			});
			
			fieldsArr[0].focus();
		},
		displayBudget: function(obj){
			var type;
			
			obj.budget >0 ? type = 'inc':type = 'exp';
			document.querySelector(DOMstrings.budgetLabel).textContent = formatNumber(obj.budget,type);
			document.querySelector(DOMstrings.incomeLabel).textContent = formatNumber(obj.totalInc,'inc');
			document.querySelector(DOMstrings.expensesLabel).textContent = formatNumber(obj.totalExp,'exp');
			if(obj.percentage >0){
				document.querySelector(DOMstrings.percentageLabel).textContent = obj.percentage + '%';
			}else{
				document.querySelector(DOMstrings.percentageLabel).textContent = '---';
			}
		},
		displayPercentages: function(percentages){
			//Access all expenses percentages using querySelectorAll method (returns node list of all percentages0
			var fields = document.querySelectorAll(DOMstrings.expensesPercLabel);
			//Create a nodelist for each function that iterates through fields and updates UI with percentages
			nodeListForEach(fields,function(current,index){
				if(percentages[index]>0){
					current.textContent = percentages[index]+'%';
				}else{
					current.textContent = '---';
				}
			});
		},
		displayMonth: function(){
			var now,year,month,months;
			now = new Date();
			year = now.getFullYear();
			months = ['January','February','March','April','May','June','July','August','September','October','November','December'];
			month = now.getMonth();
			document.querySelector(DOMstrings.dateLabel).textContent = months[month] + ' ' + year;
			
			
		},
		changedType: function(){
			var fields = document.querySelectorAll(DOMstrings.inputType + ',' + DOMstrings.inputDescription + ',' + DOMstrings.inputValue);
			nodeListForEach(fields,function(current){
				current.classList.toggle('red-focus');
			});
			
			document.querySelector(DOMstrings.inputBtn).classList.toggle('red');
		}
	};
})();

//Controller Module
var controller = (function(budgetCtrl,UICtrl){
	
	var setupEventListeners = function(){
		var DOM = UICtrl.getDOMstrings();
		//Set up event listener for when check mark is clicked
		document.querySelector(DOM.inputBtn).addEventListener('click', ctrlAddItem);
		//Set up event listener for when eter is pressed (Enter Key Code = 13)
		document.addEventListener('keypress',function(event){
			if(event.keycode ===13 || event.which ===13){
				ctrlAddItem();
			}
		});
		//Implement event delegation to container class in order to add a delete button listener to every list item that is added
		document.querySelector(DOM.container).addEventListener('click',ctrlDeleteItem);
		
		document.querySelector(DOM.inputType).addEventListener('change',UICtrl.changedType);
		
	};
	
	var updateBudget = function(){
		//1. Calculate budget
		budgetCtrl.calculateBudget();
		//2. Return budget
		var budget = budgetCtrl.getBudget();
		//3.Display budget on UI
		UICtrl.displayBudget(budget);
	};
	
	var updatePercentages = function(){
		//1. Calculate percentages
		budgetCtrl.calculatePercentages();
		//2. Read percentages from budget controller
		var percentages = budgetCtrl.getPercentages();
		//3.Update UI with new percentages
		UICtrl.displayPercentages(percentages);
	};
	
	var ctrlAddItem = function(){
		var input,newItem;
		//1. Get the field input data
		input = UICtrl.getInput();
		if(input.description !== "" && !isNaN(input.value)&& input.value > 0){
			//2. Add item to the budget controller
			newItem = budgetCtrl.addItem(input.type,input.description,input.value);
			//3. Add item to UI
			UICtrl.addListItem(newItem,input.type);
			//4. Clear description and value fields
			UICtrl.clearFields();
			//5. Calculate budget and update budget
			updateBudget();
			//6.Update expense list item percentages
			updatePercentages();
		}
	};
	
	var ctrlDeleteItem = function(event){
		var itemID,splitID,type,ID;
		//Access the ID of the deleted list item when the delete button is pressed
		itemID = event.target.parentNode.parentNode.parentNode.parentNode.id;
		//Check to make sure that ID is not Null
		console.log(itemID);
		if(itemID){
			//Split up itemID into type and ID (i.e. inc-0 = [inc,0])
			splitID = itemID.split('-');
			type = splitID[0];
			ID = parseInt(splitID[1]);
			
			//1. Delete item from data structure
			var obj = budgetCtrl.deleteItem(type,ID);
			//2. Delete item from UI
			UICtrl.deleteListItem(itemID);
			//3.Update and show new budget
			updateBudget();
			//4.Update expense list item percentages
			updatePercentages();
		}
		
	};
	
	return {
		init : function(){
			console.log('App Started');
			UICtrl.displayBudget({
				budget: 0,
				totalInc: 0,
				totalExp: 0,
				percentage: 0
			});
			setupEventListeners();
			UICtrl.displayMonth();
		}
	};
	
})(budgetController,UIController);

controller.init();

