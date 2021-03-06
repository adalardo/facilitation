#include"Individual.hpp"
#include"Random.hpp"
#include<cstdio>


Species::Species(Arena *ar,int myid, double *par) : Species(ar,myid,par[2],par[0],par[1],par[3]){}

Species::Species(Arena *ar,int myid, double death, double growth, double rep=0, double radius=0)
		:id(myid),G(growth),D(death),R(rep),Rad(radius){
	int i;
	nextStage = NULL;
	seedStage = NULL;
	dispersalRadius = 0;

	arena = ar;
	spnum = ar->getSpNum();

	interactions = (double*)malloc(spnum*(sizeof(double)));
	for(i=1;i<=spnum;i++){
		interactions[i]=0;
	}

	std::cout << id << ": G=" << G << " , R=" << R << " , D=" << D << ", Rad=" << Rad << "\n";
}

Species::~Species(){
	/* clear population */
	std::list<Individual*>::iterator i;

	for(i=population.begin();i!=population.end();i++){
		delete(*i);
	}

	free(interactions);
}

void Species::setFacilitation(double f){setInteraction(spnum,f);}
void Species::setAutoInteraction(double effect){setInteraction(id,effect);}

void Species::setInteraction(int s, double effect){
	if(effect > D){
		printf("WARNING: interaction parameter set to be bigger than deathrate. Id = %d. Parameters G=%f,R=%f,D=%f,Rad=%f,effect=%f\n", id,G,R,D,Rad,effect);
	}
	interactions[s] = effect;
	printf("effect=%f for sp=%d on sp=%d\n",effect,s,id);
}

void Species::addIndividual(double x, double y){
	if(G > 0 && nextStage==NULL) {
		printf("WARNING: Next stage set to NULL but G > 0. Check input data. Id = %d. Parameters G=%f,R=%f,D=%f,Rad=%f\n", id,G,R,D,Rad);
		throw id;
	}
	if(R > 0 && seedStage==NULL) {
		printf("WARNING: Seed stage set to NULL but R > 0. Check input data. Id = %d. Parameters G=%f,R=%f,D=%f,Rad=%f\n", id,G,R,D,Rad);
		throw id;
	}
	/*Individual *i =*/ new Individual(arena,this,x,y);
}

void Species::addIndividual(Position p){
	addIndividual(p.x,p.y);
}

void Species::disperseIndividual(double x, double y){
	Position p(x,y);
	disperseIndividual(p);
}

void Species::disperseIndividual(Position p){
	addIndividual(p + dispersalKernel());
}

Position Species::dispersalKernel(){
	Position p;
	switch(kernelType){
		case 0: /* Fully random on the arena */
			return Position(Random(arena->getWidth()),Random(arena->getHeight()));
		case 1: /* EXPONENTIAL */
		default:
			if(dispersalRadius <= 0) return Position(0,0);
			p = RandomDirection();
			return Exponential(1.0/dispersalRadius)*p;
	}
}

double Species::getTotalRate(){
	totalRate = 0;
	std::list<Individual*>::iterator i;

	for(i=population.begin();i!=population.end();i++){
		totalRate += (*i)->getTotalRate();
	}

	return totalRate;
}

bool Species::isPresent(Position p, double radius) {
	std::list<Individual*>::iterator i;

	for(i=population.begin();i!=population.end();i++){
		if((*i)->isPresent(p,radius*radius)) return true;
	}

	return false;
}

std::list<Individual*> Species::getPresent(Position p, double radius){
	std::list<Individual*>::iterator i;
	std::list<Individual*> list;

	for(i=population.begin();i!=population.end();i++){
		if((*i)->isPresent(p,radius*radius)) list.push_back(*i);
	}

	return list;
}

void Species::act(){
	std::list<Individual*>::iterator i;
	double r = Random(totalRate);
	//std::cout << "species selected. - sp=" << id << ", time=" << arena->getTotalTime() << ", size=" << population.size()<< ", r= " << r << "\n";

	for(i=population.begin();i!=population.end();i++){
		r -= (*i)->getTotalRate();
		if(r < 0) {
			(*i)->act();
			return;
		}
	}
	/* if the below code is executed, it's becase no individual was selected */
	std::cout << "WARNING: no individual selected. - sp=" << id << "\n";
}

void Species::setNextStage(Species *st) {nextStage = st;}
void Species::setSeedStage(Species *st, double dispersal, int kernel) {
	seedStage = st;
	dispersalRadius = dispersal;
	kernelType=kernel;
}

void Species::remove(std::list<Individual*>::iterator i){
	population.erase(i);
}

std::list<Individual*>::iterator Species::add(Individual *i){
	population.push_front(i);
	return population.begin();
}

Species* Species::getSeedStage() {return seedStage;}
Species* Species::getNextStage() {return nextStage;}
double Species::getG(){return G;}
double Species::getR(){return R;}
double Species::getRad(){return Rad;}
double Species::getInteraction(int species_id){return interactions[species_id];}
int Species::getId(){return id;}
double Species::getD(Position p){
	return D;
}

void Species::print(double time){
	std::list<Individual*>::iterator i;

	std::cout << "#" << population.size() << "\n";

	for(i=population.begin();i!=population.end();i++){
		std::cout << time << "," << id << ",";
		(*i)->print();
	}
}

int Species::getAbundance(){
	return population.size();
}
