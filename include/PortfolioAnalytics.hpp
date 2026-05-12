#pragma once

#include <vector>
#include <algorithm>
#include <numeric>
#include <cmath>

class PortfolioAnalytics {
public:
    struct Summary {
        double meanIRR;
        double irrStdDev;

        double irrP5;
        double irrP50;
        double irrP95;

        double meanPV;
    };

private:
    double mean(const std::vector<double>& x) {
        return std::accumulate(x.begin(), x.end(), 0.0) / x.size();
    }

    double stddev(const std::vector<double>& x, double m) {
        double v = 0.0;

        for (double xi : x) {
            v += (xi - m) * (xi - m);
        }

        return std::sqrt(v / x.size());
    }

    double percentile(std::vector<double> x, double p) {
        std::sort(x.begin(), x.end());
        size_t idx = (size_t)(p * (x.size() - 1));
        return x[idx];
    }

public:
    Summary analyze(const std::vector<double>& irr,
                    const std::vector<double>& pv) {

        Summary s;

        s.meanIRR = mean(irr);
        s.irrStdDev = stddev(irr, s.meanIRR);

        s.irrP5  = percentile(irr, 0.05);
        s.irrP50 = percentile(irr, 0.50);
        s.irrP95 = percentile(irr, 0.95);

        s.meanPV = mean(pv);

        return s;
    }
};
