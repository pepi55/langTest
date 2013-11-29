function isGeheelGetal(a){
	var antwoord = false;
	if(a%1==0)
	{
		antwoord = true;
	}
	
	return antwoord;
}

function isNatuurlijkGetal(a){
	var antwoord = false;
	if(isGeheelGetal(a) && Math.abs(a) == a)
	{
		antwoord = true;
	}

	return antwoord;
}

function isDelerVan(deeltal,deler){
	var antwoord = false;
	if(isGeheelGetal(deler/deeltal))
	{
		antwoord = true;
	}
	return antwoord;
}

function delers(a){
	var antwoord = new Array();
	if(isGeheelGetal(a) && a>1)
	{
		for(var i = 1; i <= a; i++)
		{
			if(isDelerVan(i,a))
			{
				antwoord.push(i);
			}
		}
	}
	
	return antwoord;
}
