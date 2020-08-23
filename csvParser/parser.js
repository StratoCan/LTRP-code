 var data;
	 
	function handleFileSelect(evt) {
		var file = evt.target.files[0];
		console.log('changed!');
		Papa.parse(file, {
		  header: true,
		  dynamicTyping: true,
		  complete: function(results) {
			data = results;
			console.log(results);
		  }
		});
	}
	 
	/*function createTable() {
		var array = results; 
		document.getElementById("1").innerHTML = ""; //Clear.
		
		for (i = 0; i < array.length; i++) { 
		document.getElementById("1").innerHTML += "<tr>";
			for (k = 0; k < array[0].length; k++) {
			  document.getElementById("1").innerHTML += "<td>" + array[i][k] + "</td>" ;
			}
			document.getElementById("1").innerHTML += "</tr>";
		}
	}*/