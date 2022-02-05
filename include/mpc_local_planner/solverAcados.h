#pragma once
#include "mpc_local_planner/types.h"

#include <ros/ros.h>

// standard
#include <stdio.h>
#include <stdlib.h>
// acados
#include "acados/utils/print.h"
#include "acados/utils/math.h"
#include "acados_c/ocp_nlp_interface.h"
#include "acados_c/external_function_interface.h"
#include "acados_solver_bicycle_model.h"

#define NX BICYCLE_MODEL_NX
#define NZ BICYCLE_MODEL_NZ
#define NU BICYCLE_MODEL_NU
#define NP BICYCLE_MODEL_NP
#define NBX BICYCLE_MODEL_NBX
#define NBX0 BICYCLE_MODEL_NBX0
#define NBU BICYCLE_MODEL_NBU
#define NSBX BICYCLE_MODEL_NSBX
#define NSBU BICYCLE_MODEL_NSBU
#define NSH BICYCLE_MODEL_NSH
#define NSG BICYCLE_MODEL_NSG
#define NSPHI BICYCLE_MODEL_NSPHI
#define NSHN BICYCLE_MODEL_NSHN
#define NSGN BICYCLE_MODEL_NSGN
#define NSPHIN BICYCLE_MODEL_NSPHIN
#define NSBXN BICYCLE_MODEL_NSBXN
#define NS BICYCLE_MODEL_NS
#define NSN BICYCLE_MODEL_NSN
#define NG BICYCLE_MODEL_NG
#define NBXN BICYCLE_MODEL_NBXN
#define NGN BICYCLE_MODEL_NGN
#define NY0 BICYCLE_MODEL_NY0
#define NY BICYCLE_MODEL_NY
#define NYN BICYCLE_MODEL_NYN
#define NH BICYCLE_MODEL_NH
#define NPHI BICYCLE_MODEL_NPHI
#define NHN BICYCLE_MODEL_NHN
#define NPHIN BICYCLE_MODEL_NPHIN
#define NR BICYCLE_MODEL_NR

namespace mpc
{
    // AcadosSolver::AcadosSolver(const OptVariables &optVars)
    // {
    //     init(optVars);
    //     return;
    // }

    // void AcadosSolver::init(const OptVariables &optVars)
    // {
    //     capsule = bicycle_model_acados_create_capsule();
    //     int N = BICYCLE_MODEL_N;
    //     // allocate the array and fill it accordingly
    //     double *new_time_steps = NULL;
    //     int status = bicycle_model_acados_create_with_discretization(capsule, N, new_time_steps);
    //     config = bicycle_model_acados_get_nlp_config(capsule);
    //     dims = bicycle_model_acados_get_nlp_dims(capsule);
    //     in = bicycle_model_acados_get_nlp_in(capsule);
    //     out = bicycle_model_acados_get_nlp_out(capsule);
    //     solver = bicycle_model_acados_get_nlp_solver(capsule);
    //     opts = bicycle_model_acados_get_nlp_opts(capsule);
    //     if (status)
    //     {
    //         printf("bicycle_model_acados_create() returned status %d. Exiting.\n", status);
    //         exit(1);
    //     }

    //     // initialization for state values
    //     double x_init[NX];
    //     x_init[0] = optVars.x.x;
    //     x_init[1] = optVars.x.y;
    //     x_init[2] = optVars.x.psi;
    //     x_init[3] = optVars.x.vel;
    //     x_init[4] = optVars.u.delta;

    //     // initial value for control input
    //     double u0[NU];
    //     u0[0] = 0.0;
    //     u0[1] = 0.0;

    //     // initialize solution
    //     for (int i = 0; i <= dims->N; i++)
    //     {
    //         ocp_nlp_out_set(config, dims, out, i, "x", x_init);
    //         ocp_nlp_out_set(config, dims, out, i, "u", u0);
    //     }
    //     return;
    // }

    // void AcadosSolver::freeAllocated()
    // {
    //     // free solver
    //     int status = bicycle_model_acados_free(capsule);
    //     if (status)
    //     {
    //         ROS_ERROR("bicycle_model_acados_free() returned status %d. \n", status);
    //     }
    //     // free solver capsule
    //     status = bicycle_model_acados_free_capsule(capsule);
    //     if (status)
    //     {
    //         ROS_ERROR("bicycle_model_acados_free_capsule() returned status %d. \n", status);
    //     }
    //     return;
    // }
    class AcadosSolver
    {
    public:
        AcadosSolver(const OptVariables &optVars)
        {
            init(optVars);
            return;
        }
        bicycle_model_solver_capsule *capsule;
        ocp_nlp_config *config;
        ocp_nlp_dims *dims;
        ocp_nlp_in *in;
        ocp_nlp_out *out;
        ocp_nlp_solver *solver;
        void *opts;
        ~AcadosSolver()
        {
            freeAllocated();
        }
        void reInit(const OptVariables &optVars)
        {
            freeAllocated();
            init(optVars);
        }

    private:
        void init(const OptVariables &optVars)
        {
            capsule = bicycle_model_acados_create_capsule();
            int N = BICYCLE_MODEL_N;
            // allocate the array and fill it accordingly
            double *new_time_steps = NULL;
            int status = bicycle_model_acados_create_with_discretization(capsule, N, new_time_steps);
            config = bicycle_model_acados_get_nlp_config(capsule);
            dims = bicycle_model_acados_get_nlp_dims(capsule);
            in = bicycle_model_acados_get_nlp_in(capsule);
            out = bicycle_model_acados_get_nlp_out(capsule);
            solver = bicycle_model_acados_get_nlp_solver(capsule);
            opts = bicycle_model_acados_get_nlp_opts(capsule);
            if (status)
            {
                printf("bicycle_model_acados_create() returned status %d. Exiting.\n", status);
                exit(1);
            }

            // initialization for state values
            double x_init[NX];
            x_init[0] = optVars.x.x;
            x_init[1] = optVars.x.y;
            x_init[2] = optVars.x.psi;
            x_init[3] = optVars.x.vel;
            x_init[4] = optVars.u.delta;

            // initial value for control input
            double u0[NU];
            u0[0] = 0.0;
            u0[1] = 0.0;

            // initialize solution
            for (int i = 0; i <= dims->N; i++)
            {
                ocp_nlp_out_set(config, dims, out, i, "x", x_init);
                ocp_nlp_out_set(config, dims, out, i, "u", u0);
            }
            return;
        }
        void freeAllocated()
        {
            // free solver
            int status = bicycle_model_acados_free(capsule);
            if (status)
            {
                ROS_ERROR("bicycle_model_acados_free() returned status %d. \n", status);
            }
            // free solver capsule
            status = bicycle_model_acados_free_capsule(capsule);
            if (status)
            {
                ROS_ERROR("bicycle_model_acados_free_capsule() returned status %d. \n", status);
            }
            return;
        }
    };
}