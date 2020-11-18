#include <iostream>

using std::cout;
using std::endl;

#include <string>

using std::string;

#include <fstream>
#include <chrono>

#include <representations/SolutionWithGraph.hpp>
#include <representations/Instance.hpp>
#include <io/InstanceReader.hpp>
#include <solver/TrivialSolver.hpp>

bool fexists(const string &filename) {
    std::ifstream ifile(filename.c_str());
    return (bool) ifile;
}

// didn't know this, but abort() is an internal name
void abortProgram() {
    cout << "Could not parse command line arguments!\n"
         << "Make sure that all cmd arguments were spelled correctly and that files exist." << endl;
}

void checkFeasibility(const string &filename) {

    Instance instance;
    SolutionWithGraph solution(instance);
    readInstance(filename, instance, solution);

    if (solution.isFeasible()) {
        cout << solution.size() << endl;
    }

}

void solve(const string &infile, const string &outfile) {

    Instance instance;
    SolutionWithGraph sol(instance);
    readInstance(infile, instance, sol);

    // instance.showPoints();

    auto start = std::chrono::high_resolution_clock::now();
    TrivialSolver trivialSolver;
    SolutionWithGraph solution = trivialSolver.solve(instance);
    auto finish = std::chrono::high_resolution_clock::now();

    std::chrono::duration<double> elapsed = finish - start;

    std::cout << solution.size() << "\t" << elapsed.count() << std::endl;

    std::ofstream out(outfile);
    solution << out;
    out.close();

}

int main(int argc, char *argv[]) {

    try {

        if (argc == 3) {
            string eval = argv[1];
            if (eval == "-eval" && fexists(argv[2])) {
                checkFeasibility(argv[2]);
            } else {
                abortProgram();
                return 0;
            }
        } else if (argc == 5) {
            string in = argv[1];
            string out = argv[3];
            if (in == "-in" && out == "-out" && fexists(argv[2])) {

                solve(argv[2], argv[4]);

            } else {
                abortProgram();
                return 0;
            }

        } else {
            cout << "This program can be started with either one or two command line arguments.\n"
                 << "Call './solver -in dat1 -out dat2' to read in dat1, run the algorithm and write the solution to dat2.\n"
                 << "Call './solver -eval dat1' to read in dat1 and check a solution for feasibility."
                 << endl;
        }
        return 0;

    } catch (const std::exception &e) {
        cout << "ERROR: " << e.what() << endl;
    }
}