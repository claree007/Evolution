#include<iostream>
#include<conio.h>
#include<string.h>
#include<stdlib.h>
#include<math.h>
#include<ctime>

// Wubba lubba dub dub!

using namespace std;

char str[] = "Wubba lubba dub dub!";

const int len = sizeof(str)-1, n = 1000;


class individual
{
	public:
	char a[len], parent[len];
	float fitness;
	individual()
	{
		strcpy(a,str);
	}
	void target_string()
	{
		int i;
		for(i=0; i<len; i++)
		{
			cout<<a[i];	
		}
		cout<<endl;
	}
	int fitness_test();
	void print();
	void print(individual[]);
	void sort(individual[]);
	void exchange(individual&, individual&);
};

class evo
{
	int evolutions, mutations, deaths;
    float average;
    
	public:
		evo()
	    {
			evolutions = 0;
			mutations = int(0.1 * n + 0.5); // % mutations
			deaths = int(0.5 * n + 0.5); // % deaths
		}
		void generate(individual[]);
		void crossover(individual[]); // evolution
		void increase()
		{
			cout<<"No. of evolutions: "<<++evolutions<<endl;
		}
		void average_fitness(individual p[])
		{
			int i;
			average = 0.0;
			for(i=0; i<n; i++)
			{
				average += p[i].fitness;
			}
			cout<<"Average fitness: "<<average/n<<"%"<<endl;
		}
		void death(individual[]);
		void mutation(individual[]);
};



void evo::generate(individual p[])
{
    int i, j;
    for(i=0; i<n; i++)
    {
    	for(j=0; j<len; j++)
		{
			p[i].parent[j] = char((rand() % 92)+ 32);
		}
		//p[i].print();
	    p[i].fitness = p[i].fitness_test(); // rate fitness
	}
}

void individual::print() // print individual
{
	int j;
	for(j=0; j<len; j++)
	{
		cout<<parent[j];
	}
	cout<<endl;
}

void individual::print(individual p[])// print an array of individuals
{
	int i, j;
	for(i=0; i<n; i++)
	{
		for(j=0; j<len; j++)
		{
			cout<<p[i].parent[j];
		}
		cout<<endl;
	}
	cout<<endl;
}

int individual::fitness_test()
{
    int i, j;
	float f = 0;
    for(i=0; i<len; i++)
    {
    	//cout<<"a[i]= "<<a[i]<<" "<<"parent[i]= "<<parent[i]<<endl;
		if(a[i] == parent[i]) f++;
	}
	return ((f/len)*100);
}

void individual::sort(individual p[]) // sort parents by fitness
{
	// bubble sort
	int k=1, i;
	float temp;
	while(k == 1)
	{
		k = 0;
		for(i=0; i<n-1; i++)
		{
			if(p[i].fitness < p[i+1].fitness)
			{
				k = 1;
				//cout<<p[i].fitness<<','<<p[i+1].fitness<<endl;
				//for fitness array
				temp = p[i].fitness;      // for now i am storing the values of fitness just to print and check
				p[i].fitness = p[i+1].fitness;
				p[i+1].fitness = temp;
				
				//for parent array
				exchange(p[i], p[i+1]);
			}
		}
	}
	//print(p);
}

void individual::exchange(individual& p1, individual& p2)
{
	int i, j;
	char s0[len];
	for(i=0; i<len; i++)
	{
		s0[i] = p1.parent[i];
		p1.parent[i] = p2.parent[i];
		p2.parent[i] = s0[i];
	}
}

void evo::crossover(individual p[])
{
	// randomly choose 2 parents and produce a string containing 1st half and 2nd of parents respectively
	int i, j, k, a, b, m, t=0, fit[n], y[2], u;
	char e, f;
	individual arr[n];
	// make array for probability
	for(i=0; i<n-deaths; i++)
	{
		fit[i] = int(abs((p[i].fitness/10)+1));
		//cout<<fit[i];
		t+= fit[i];
	}
	//cout<<"total fitness: "<<t<<endl;
	int array[t];
	for(i=0, m=0; i<t; i++, m++)
	{
		for(j=0; j<fit[m]; j++)
		{
			array[i] = m;
			//cout<<i<<": "<<array[i]<<endl;
			i++;
		}
		i--;
	}
	
	for(k=n-deaths; k<n; k++)
	{
		for(i=0; i<=1; i++)
		{
			a = array[rand() % t];
			b = array[rand() % t];
			y[i] = p[a].fitness > p[b].fitness ? a : b;
		}
		//p[y[0]].print();
		//p[y[1]].print();
		//u = array[rand() % t];
		//u = rand() % n;
		for(i=0, j=len-1; i<len/2, j>=len/2; i++, j--)
		{
			//p[u].parent[i] = p[y[0]].parent[i];
			//p[u].parent[j] = p[y[1]].parent[j];
			//arr[k].parent[i] = p[y[0]].parent[i];
			//arr[k].parent[j] = p[y[1]].parent[j];
			p[k].parent[i] = p[y[0]].parent[i];
			p[k].parent[j] = p[y[1]].parent[j];
		}
		//check fitness
		//arr[k].write_fitness(arr[k].fitness_test()); // delete this step as it is repeated
		//p[u].fitness = p[u].fitness_test();
		p[k].fitness = p[k].fitness_test();
	}
	// replace previous individuals(string and fitness) with new arr instances
	/*
	for(k=0; k<n; k++)
	{
		p[k].fitness = arr[k].fitness_test();
		individual().exchange(arr[k], p[k]);
	}
	*/
}

void evo::death(individual p[])
{
	int i, j, k, f=0, fit[n], a, b;
	
	for(i=0; i<n; i++)
	{
		fit[i] = abs(100 - p[i].fitness)/10+1;
		//cout<<fit[i];
		f+= fit[i];
	}
	//cout<<f;
	//getch();
	int array[f];
	for(i=0, k=0; i<f; i++, k++)
	{
		for(j=0; j<fit[k]; j++)
		{
			array[i] = k;
			//cout<<i<<": "<<array[i]<<" j: "<<j<<" k: "<<k<<endl;
			i++;
		}
		i--;
	}
	for(i=0; i<deaths; i++)
	{
		//cout<<i<<endl;
		a = rand() % f;
		b = array[a];
		while(p[b].parent[0] == '\0')
		{
			a = rand() % f;
			b = array[a];
			//cout<<"loop here"<<endl;
		}
		p[b].parent[0] = '\0';
		p[b].fitness = -1;
	}
}

void evo::mutation(individual p[])
{
	int i, pos, s;
	char c;
	for(i=0; i<mutations; i++)
	{
		s = rand() % n; // random string for mutation
		c = (rand() % 92)+32; // random character as mutation
		pos = rand() % len;
		//cout<<"Original string: ";
		//p[s].print();
		p[s].parent[pos] = c;
		p[s].fitness = p[s].fitness_test();
		//cout<<endl<<"New string: ";	
		//p[s].print();	
	}
}


int main()
{
    int i, f=0;
	char c;
    srand(time(0));
    evo person;
    individual p[n];
    
    cout<<"Start generating individuals? [Y/N]";
	c = getch();
	
	//generating random strings and rate fitness
	person.generate(p);
	
	while(c == 'y' || c == 'Y')
	{
		system("cls");
		//f = 1;
		//p[0].print(p);
		person.increase(); //increase evolution count
    	//cout<<"Sort 1:"<<endl;
		individual().sort(p);
		//cout<<"Out of sort"<<endl;
		//p[0].print(p);
    	person.average_fitness(p);
	    //getch();
	    cout<<"Current best string: ";
		p[0].print();
		if(p[0].fitness == 100)
		{
			cout<<"String generated!!!"<<endl;
			cout<<"Original string: ";
			individual().target_string();
			cout<<endl;
			cout<<"Generated string: ";
			p[0].print();
			//cout<<endl;
			break;
		}
		//cout<<"In death:"<<endl;
	    person.death(p);
		//cout<<"Out of death:"<<endl;
		//p[0].print(p);
		//cout<<"Sort 2:"<<endl;
		individual().sort(p);
		//p[0].print(p);
		//cout<<"Crossover:"<<endl;
	    person.crossover(p);
	    //p[0].print(p);
		//getch();
		//cout<<"Mutation:"<<endl;
	    person.mutation(p);
	    //c = getch();
		//p[0].print(p);
		//getch();
	}
	exit(0);
	//system("cls"); 
}




/*
for(i=0; i<=1; i++)
{
	do
	{
		a = array[rand() % t];
		b = array[rand() % t];
		//a = rand() % n;
		//b = rand() % n;
		//e = p[a].read_string(0);
		//f = p[b].read_string(0);
	} while(p[a].parent[0] == '\0' || p[b].parent[0] == '\0'); //(e == '\0' || f == '\0');
	y[i] = p[a].fitness > p[b].fitness ? a : b;
}
*/
