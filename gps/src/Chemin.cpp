#include "Chemin.hpp"
#include <limits>
#include <queue>
#include <sstream>

using namespace std;

/// \brief implémentation interne pour le calcul de plus court chemin
/// 
struct Parcours_ {
    Chemin cheminParcouru_;
    Chemin cheminRestant_;
    int distanceParcourue_;
};

Chemin Chemin::calculerPlusCourt(const string & ville1, 
        const string & ville2) const {

    if (routes_.empty())
        throw string("Chemin::calculerPlusCourt : routes_.empty()");

    if (ville1 == ville2)
        throw string("Chemin::calculerPlusCourt : ville1 == ville2");

    Chemin meilleurChemin;
    int meilleureDistance = std::numeric_limits<int>::max();
    queue<Parcours_> fileParcours;
    // initialise la file de parcours
    {
        Chemin cheminAvec, cheminSans;
        partitionner(ville1, cheminAvec, cheminSans);
        for (const Route & r : cheminAvec.routes_) {
            Chemin c;
            c.routes_.push_back(r);
            fileParcours.push(Parcours_{c, cheminSans, r.distance_});
        }
    }

    // teste tous les parcours
    while (not fileParcours.empty()) {
        const Parcours_ & parcoursCourant = fileParcours.front();
        const string & villeEtape 
            = parcoursCourant.cheminParcouru_.routes_.back().villeB_;
        if (villeEtape == ville2 
                and parcoursCourant.distanceParcourue_ < meilleureDistance) {
            meilleurChemin = parcoursCourant.cheminParcouru_;
            meilleureDistance = parcoursCourant.distanceParcourue_;
        }
        else if (villeEtape != ville1) {
            Chemin cheminAvec, cheminSans;
            const Chemin & cheminRestant = parcoursCourant.cheminRestant_;
            cheminRestant.partitionner(villeEtape, cheminAvec, cheminSans);
            for (const Route & r : cheminAvec.routes_) {
                Chemin c(parcoursCourant.cheminParcouru_);
                c.routes_.push_back(r);
                int d = parcoursCourant.distanceParcourue_ + r.distance_;
                fileParcours.push(Parcours_{c, cheminSans, d});
            }
        }
        fileParcours.pop();
    }

    return meilleurChemin;
}

void Chemin::partitionner(const string & ville, Chemin & cheminAvec, 
        Chemin & cheminSans) const {

    // TODO

}

void Chemin::importerCsv(istream & is) {
 std::string contenu;

      do{
      getline(is,contenu);
      Route r;
      istringstream str(contenu);
      str >> r;
      routes_.push_back(r);}while(!is.eof());
      

}

void Chemin::exporterDot(ostream & os, const string & ville1, 
        const string & ville2) const {
   ofstream fichier("finistere.dot",ios::out);
  if(fichier)
    {
      fichier << "graph { \n";
      fichier <<"splines=line; \n";
      Chemin court = calculerPlusCourt(ville1,ville2);
      for(int i=0;i<court.routes_.size();i++)
	{
	  if(i ==0)
	     fichier << court.routes_[i].villeA_ << " -- " << court.routes_[i].villeB_;
	  else
	    fichier << " -- " <<court.routes_[i].villeB_ ;
	}
      fichier << " [color=red, penwidth=3]; \n";

      for(int i=0;i<routes_.size();i++)
	{
	  fichier << routes_[i].villeA_ << " -- " << routes_[i].villeB_ << " [label="<< routes_[i].distance_<<"]; \n";
	}
    
      fichier << "}";
      fichier.close();
  
}

  
}
