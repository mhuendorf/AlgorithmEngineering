#include <iostream>
using std::cout;
using std::endl;

#include <string>
using std::string;

#include <fstream>
#include <chrono>

#include <representations/Instance.hpp>
#include <representations/Solution.hpp>
#include <io/InstanceReader.hpp>
#include <solver/TrivialSolver.hpp>

bool fexists(const string& filename) {
  std::ifstream ifile(filename.c_str());
  return (bool) ifile;
}

// didn't no this, but abort() is an internal name
void abortMyProgram() {
    cout << "Could not parse command line arguments!\n" 
        << "Make sure that all cmd arguments were spelled correctly and that files exist." << endl;
}

void checkFeasibility(const string& filename) {

    Instance instance;
    Solution solution(instance);
    readInstanceAndSolution(instance, solution, filename);

    if(!solution.isFeasible()) {
        throw std::runtime_error("Solution was not feasible!");
    }

}

void solve(const string& infile, const string& outfile) {

    Instance instance;
    readInstance(instance, infile);

    auto start = std::chrono::high_resolution_clock::now();
    TrivialSolver trivialSolver;
    Solution sol = *trivialSolver.solve(instance);
    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;

    std::cout << sol.countLabelledPoints() << "\t" << elapsed.count() << std::endl;

    std::ofstream out(outfile);
    out << sol << std::endl;
    out.close();

}

int main(int argc, char* argv[]) {

    try {
    
        if(argc == 3) {
            string eval = argv[1];
            if(eval.compare("-eval") == 0 && fexists(argv[2])) {
                checkFeasibility(argv[2]);
            } else {
                abortMyProgram();
                return 0;
            }
        } else if(argc == 5) {
            string in = argv[1];
            string out = argv[3];
            if( in.compare("-in") == 0 && out.compare("-out") == 0 && fexists(argv[2]) ) {
                
                solve(argv[2], argv[4]);

            } else {
                abortMyProgram();
                return 0;
            }

        } else {
            cout << "This program can be started with either one or two command line arguments.\n"
                << "Call './solver -in dat1 -out dat2' to read in dat1, run the algorithm and write the solution to dat2.\n"
                << "Call './solver -eval dat1' to read in dat1 and check a solution for feasibility."
                << endl;
        }
        return 0;
    
    } catch(const std::exception& e) {
        cout << "ERROR: " << e.what() << endl;
    }
}