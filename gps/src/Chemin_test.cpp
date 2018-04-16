#include <CppUTest/CommandLineTestRunner.h>

#include "Chemin.hpp"
#include <fstream>
#include <sstream>

/// \brief implémentation interne pour les tests unitaires sur membres privés
/// 
class Chemin_test_ : public Chemin {

    public:

        Chemin_test_() = default;
        Chemin_test_(const Chemin_test_ & c) = default;
        Chemin_test_(const Chemin & c) : Chemin(c) {}

        void importerCsv_0() {
            Chemin_test_ c;
            std::ifstream infile("test1.csv");
            c.importerCsv(infile);
            CHECK_EQUAL("toto", c.routes_.back().villeA_);
        }

        void exporterDot_0() { 
            try {
                Chemin_test_ c;
                std::ostringstream oss;
                c.exporterDot(oss, "toto", "tata");
                FAIL("failed to throw exception");
            }
            catch (const std::string & msg) {
                CHECK_EQUAL("Chemin::calculerPlusCourt : routes_.empty()", msg);
            }
        }

};

TEST_GROUP(GroupChemin) { };
TEST(GroupChemin, importerCsv_0) { Chemin_test_().importerCsv_0(); }
TEST(GroupChemin, exporterDot_0) { Chemin_test_().exporterDot_0(); }

