#include<iostream>
#include<fstream>
#include<string.h>
#include<windows.h>
#include<vector>
using namespace std;


struct player
{
	string name;
	int kill;
	int death;
	float rateo;
	bool connect;
	int punteggio;
	int autokill;
	
};

int main()
{
	player p;
	int Nplayer;
	vector<player> v(50);
	string n,BeforeN,NomeDelMorto;


while(true)
{
	ifstream i("players.txt");


	//vedo quanti e i nomi dei player
	 Nplayer = 0;
	while(!i.eof())
	{
		i >> v.at(Nplayer).name;
		v.at(Nplayer).name= v.at(Nplayer).name+"^7";
		v.at(Nplayer).kill = 0;
		v.at(Nplayer).death = 0;
		v.at(Nplayer).autokill = 0;
		v.at(Nplayer).rateo = 0.00;
		v.at(Nplayer).punteggio = 0;
		v.at(Nplayer).connect = false;
		Nplayer ++;

	}
	i.close();

	for(int i = 0; i<Nplayer;i++)
	{
		//ifstream in("../Giochi/openarena-0.8.8/stderr.txt");
		ifstream in("../stderr.txt");	
		while (!in.eof())
		{
			BeforeN = n;
			in >> n;
			//cout<<n<<endl;
			if(n == v.at(i).name || n == v.at(i).name+"'s")
			{
				NomeDelMorto = n; 
				in >> n;
				
				// Se fa una kill
				if( BeforeN == "by" || BeforeN == "was" || BeforeN == "almost" || BeforeN == "ate")
				{
					
					v.at(i).kill = v.at(i).kill + 1;
				}
				
				 
				// Se il nome è uguale all'ultima parola sopra 
				if(	n == NomeDelMorto || n == NomeDelMorto+"'s" )
				{
					in >> n;
					if( n == "was" || n == "almost" || n == "ate" || n == "blew" || n == "sank" || n == "cratered." || n == "melted" || n == "tripped")
					{
						v.at(i).death = v.at(i).death + 1;
						if(n == "blew" || n == "sank" || n == "cratered." || n == "melted" || n == "tripped") v.at(i).autokill++;
						
					}

				}

				// Se è morto
				else if( n == "was" || n == "almost" || n == "ate" || n == "blew" || n == "sank" || n == "cratered." || n == "melted" || n == "tripped")
				{
					v.at(i).death = v.at(i).death + 1;
					if(n == "blew" || n == "sank" || n == "cratered." || n == "melted" || n == "tripped") v.at(i).autokill++;

				}
				if( n == "entered")
				{
					v.at(i).connect = true;	
				}
				
				if( n == "disconnected")
				{
					v.at(i).connect = false;	
				}				
				
				
				
			} 
		}
		
		// calcolo del rateo
		float kill = v.at(i).kill;
		float death = v.at(i).death; 
		v.at(i).rateo = kill / death;
		// calcolo punteggio finale
		v.at(i).punteggio = (kill * 100)-(v.at(i).autokill*20);
		v.at(i).punteggio =v.at(i).punteggio+ ( v.at(i).rateo* (v.at(i).punteggio/10));
		if(v.at(i).punteggio < 0)v.at(i).punteggio = 0;
		
		// ordinamento classifica	
		for(int i = 0; i<Nplayer-1;i++)
		{
			for(int j = 0; j<Nplayer-1;j++)
			{
				if(v.at(i).punteggio > v.at(j).punteggio )
				{
					player p;
					p = v.at(j);
					v.at(j) = v.at(i);
					v.at(i) = p;
				}
			}
		}
		
	}
	
	// STAMPO PAGINA HTML
	ofstream out("index.html");
	out<<"<head>"<<endl;
	out<<"<meta http-equiv=" <<"refresh"<<" content=" <<"3>" <<endl;
	out<<"<link rel=" <<"stylesheet" <<" type=" <<"text/css" << " href=" <<"css/style.css />"<<endl;
	out<<"</head>"<<endl;
	out<<"<table>"<<endl;
	
	out<<"<body>"<<endl;
	out<<"<tr>"<<endl;
	out<<"<th>"<< "Posizione" <<"</th>"<<endl;
	out<<"<th>"<< "Nome" <<"</th>"<<endl;
	out<<"<th>"<< "Punteggio" <<"</th>"<<endl;
	out<<"<th>"<< "Kill" <<"</th>"<<endl;
	out<<"<th>"<< "Death" <<"</th>"<<endl;
	out<<"<th>"<< "Autokill" <<"</th>"<<endl;
	out<<"<th>"<< "Rateo" <<"</th>"<<endl;
	out<<"<th>"<< "Connesso" <<"</th>"<<endl;
	out<<"</tr>"<<endl;
	
	for(int i = 0; i<Nplayer-1;i++)
	{
		out<<"<tr>";
		out<<"<td>"<< i+1 <<"</td>"<<endl;
		string nome;
		nome = v.at(i).name;
		nome.erase(nome.size()-2);
		out<<"<td>"<< nome <<"</td>"<<endl;
		out<<"<td>"<<v.at(i).punteggio <<"</td>"<<endl;
		out<<"<td>"<<v.at(i).kill <<"</td>"<<endl;
		out<<"<td>"<< v.at(i).death <<"</td>"<<endl;
		out<<"<td>"<< v.at(i).autokill <<"</td>"<<endl;
		out<<"<td>"<< v.at(i).rateo <<"</td>"<<endl;
		if(v.at(i).connect == true) out<<"<td>"<<"<span style="<<"color:green>"<< "Connesso" <<"</span>"<<"</td>"<<endl;
		else out<<"<td>"<<"<span style="<<"color:red>"<< "Disconnesso" <<"</span>"<<"</td>"<<endl;
		out<<"</tr>"<<endl;
	}
	out<<"</table>"<<endl;
	out<<"</body>"<<endl;	
	out.close();
Sleep(2000);
}
return 0;
	
}
