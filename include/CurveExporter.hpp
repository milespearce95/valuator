#pragma once

#include <vector>
#include <fstream>
#include "PortfolioMonteCarlo.hpp"

class CurveExporter {
public:
    void exportSurvival(const std::vector<PortfolioMonteCarlo::SurvivalPoint>& curve,
                        const std::string& filename) {

        std::ofstream file(filename);

        file << "month,survival\n";

        for (const auto& p : curve) {
            file << p.month << "," << p.survivalRate << "\n";
        }
    }

    void exportDefault(const std::vector<PortfolioMonteCarlo::DefaultPoint>& curve,
                       const std::string& filename) {

        std::ofstream file(filename);

        file << "month,default\n";

        for (const auto& p : curve) {
            file << p.month << "," << p.defaultRate << "\n";
        }
    }
};
