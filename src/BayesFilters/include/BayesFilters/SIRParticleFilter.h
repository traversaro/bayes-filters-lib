#ifndef SIRPARTICLEFILTER_H
#define SIRPARTICLEFILTER_H

#include "FilteringAlgorithm.h"
#include "PFCorrection.h"
#include "PFPrediction.h"
#include "Resampling.h"

#include <memory>

#include <Eigen/Dense>

namespace bfl {
    class SIRParticleFilter;
}


class bfl::SIRParticleFilter : public FilteringAlgorithm
{
public:
    SIRParticleFilter() = delete;

    SIRParticleFilter(std::unique_ptr<PFPrediction> prediction, std::unique_ptr<PFCorrection> correction, std::unique_ptr<Resampling> resampling) noexcept;

    SIRParticleFilter(SIRParticleFilter&& sir_pf) noexcept;

    ~SIRParticleFilter() noexcept override;

    SIRParticleFilter& operator=(SIRParticleFilter&& sir_pf) noexcept;

    void initialization() override;

    void filteringStep() override;

    void getResult() override;

    bool runCondition() override { return (getFilteringStep() < simulation_time_); };

protected:
    std::unique_ptr<PFPrediction> prediction_;
    std::unique_ptr<PFCorrection> correction_;
    std::unique_ptr<Resampling>   resampling_;

    int                           simulation_time_;
    int                           num_particle_;
    int                           surv_x_;
    int                           surv_y_;

    Eigen::MatrixXf               object_;
    Eigen::MatrixXf               measurement_;

    Eigen::MatrixXf               init_particle_;
    Eigen::VectorXf               init_weight_;

    std::vector<Eigen::MatrixXf>  result_particle_;
    std::vector<Eigen::VectorXf>  result_weight_;

    void snapshot();
};

#endif /* SIRPARTICLEFILTER_H */
