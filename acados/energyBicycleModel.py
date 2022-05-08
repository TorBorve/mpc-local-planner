from re import L, M
from socket import NI_NUMERICHOST
from this import d
from xml.etree.ElementTree import C14NWriterTarget
from attr import NOTHING
import numpy as np
from casadi import *
from acados_template import AcadosOcp, AcadosSimSolver, AcadosModel, AcadosOcpSolver
from requests import delete
import yaml 


# def energyBicycleModel():

#     constraint = types.SimpleNamespace()
#     model = types.SimpleNamespace()

#     modelName = "Bicycle_model"

#     # Parameters
#     r = 0.2 # Radius of wheel [m]
#     m = 60 # Mass of vehicle [kg]
#     Cr = 0.015 # Rolling resistance
#     Cd = 0.45 # Drag coefficient
#     rho = 0.5 # Air resistance [kg/m³]
#     A = 20 # Frontal area [m²]
#     g = 9.81 # Gravity constant [m/s²]
#     G = 7 # Total reduction ratio'
#     lr = 1.5 # Distance from center to rear wheel [m]
#     lf = 1.5 # Distance from center to front wheel [m]


#     # States
#     x1 = SX.sym("x1") # X-position
#     y1 = SX.sym("y1") # Y-position
#     psi = SX.sym("psi") # Angle of car
#     v = SX.sym("v") # Velocity
#     delta = SX.sym("v") # Steering angle
#     omega = SX.sym("v") # Angular velocity

#     x = vertcat(x1, y1, psi, v, delta, omega) # States

#     # Controls
#     delta_dot = SX.sym("delta_dot") # Steering angle
#     omega_dot = SX.sym("omega_dot") # Angular velocity

#     u = vertcat(delta_dot, omega_dot) # Inputes

#     # xdot
#     x1Dot = SX.sym("x1_dot")
#     y1Dot = SX.sym("y1_dot")
#     psiDot = SX.sym("psi_dot")
#     vDot = SX.sym("v_dot")

#     xDot = vertcat(x1Dot, y1Dot, psiDot, vDot)

#     # Dynamics
#     beta = lr / (lr + lf) * delta
#     f_expl = vertcat(
#         v * cos(psi + beta),
#         v * sin(psi + beta),
#         v/lr * sin(beta),
#         omega_dot * r * cos(beta), # Not sure about this one. Need to talk to professor or Tor. It has to most likely contain something with torque
#         delta_dot,
#         omega_dot
#     )

    

#     # Constraints


#     # Define model struct
#     params = types.SimpleNamespace()
#     params.r = r
#     params.m = m
#     params.Cr = Cr
#     params.Cd = Cd
#     params.rho = rho
#     params.A = A
#     params.g = G
#     params.G = G
#     params.lr = lr
#     params.lf = lf
#     model.f_impl_expr = xDot - f_expl
#     model.f_expl_expr = f_expl
#     model.x = x
#     model.xdot = xDot
#     model.u = u
#     model.name = modelName
#     model.params = params

#     return model, constraint

    
# def costFnc(model):

#     r = 0.2 # Radius of wheel [m]
#     m = 60 # Mass of vehicle [kg]
#     Cr = 0.015 # Rolling resistance
#     Cd = 0.45 # Drag coefficient
#     rho = 0.5 # Air resistance [kg/m³]
#     A = 20 # Frontal area [m²]
#     g = 9.81 # Gravity constant [m/s²]
#     G = 7 # Total reduction ratio'


#     x1 = model.x[0]
#     y1 = model.x[1]
#     psi = model.x[2]
#     v = model.x[3]
#     delta = model.x[4]
#     omega = model.x[5]

#     delta_dot = model.u[1]
#     omega_dot = model.u[2]

#     a = model.xdot[3]

#     Tm = r/G * (m*a + m*g*Cr + 1/2*rho*Cd*A*v**2)

#     energi = Tm * omega

#     yawPath = ...
#     epsi = yawPath - psi
#     yPath = ...
#     cte = yPath - y1

#     return vertcat(cte, epsi, v, delta_dot, omega_dot, energi)




def energyBicycleModel(params):
    
    modelName = "BicycleModel"

    # Constants

    

    r = params["radius"] # Wheel radius
    l = params["wheelbase"] # Distance between front wheel and rear wheel
    G = params["gear_ratio"] # Gear ratio
    m = params["mass_car"]# Mass of car
    V = params["voltage"] # Voltage
    Cd = params["drag_coefficient"] # Drag coefficient
    rho = params["air_resistance"]# Air resistance [kg/m³]
    A = params["frontal_area"]# Frontal area [m²]

    # States

    x1 = SX.sym("x1") # X-position
    y1 = SX.sym("y1") # Y-position
    psi = SX.sym("psi") # Angle of car
    v = SX.sym("v") # Velocity of car
    #omega = SX.sym("omega") # Angular velocity
    delta = SX.sym("delta") # Steering angle
    throttle = SX.sym("throttle")


    x = vertcat(x1, y1, psi, v, delta, throttle)

    # Input
    
    #omega_dot = SX.sym("omega_dot") # Angular acceleration
    delta_dot = SX.sym("delta_dot") # Steering angle derivative
    throttle_dot = SX.sym("throttle_dot")

    u = vertcat(delta_dot, throttle_dot)

    x1Dot = SX.sym("x1_dot")
    y1Dot = SX.sym("y1_dot")
    psiDot = SX.sym("psi_dot")
    a = SX.sym("a")
    #omega_dot_state = SX.sym("omega_dot_state")
    delta_dot_state = SX.sym("delta_dot_state")
    throttle_dot_state = SX.sym("throttle_dot_state")

    xDot = vertcat(x1Dot, y1Dot, psiDot, a, delta_dot_state, throttle_dot_state)

    f_expl = vertcat(
        v * (cos(psi)), # * cos(psi) - sin(delta)/2 * sin(psi)),
        v * (sin(psi)), # * sin(psi) + sin(delta)/2 * cos(psi)),
        v * sin(delta)/l,
        V * 3.2 * throttle * r / (v * G * m + 1) - (1/2*(rho*Cd*A*(v)**2) / m), #5*throttle - 0.03*v,
        delta_dot,
        throttle_dot
    )    

    p = vertcat(SX.sym("coeff_0"), SX.sym("coeff_1"), SX.sym("coeff_2"), SX.sym("coeff_3"))

    f_impl = xDot - f_expl
    model = AcadosModel()

    model.name = modelName
    model.f_expl_expr = f_expl
    model.f_impl_expr = f_impl
    model.xdot = xDot
    model.x = x
    model.u = u
    model.p = p

    return model

def costFnc(model):

    with open("../params/mpc.yaml", "r") as paramFile:
        params = yaml.safe_load(paramFile)

    r = params["radius"] # Radius of wheel [m]
    m = params["mass_car"] # Mass of vehicle [kg]
    Cr = params["rolling_resistance"] # Rolling resistance
    Cd = params["drag_coefficient"] # Drag coefficient
    rho = params["air_resistance"] # Air resistance [kg/m³]
    A = params["frontal_area"] # Frontal area [m²]
    g = params["gravity_constant"]# Gravity constant [m/s²]
    G = params["total_reduction_ratio"]# Total reduction ratio


    x1 = model.x[0]
    y1 = model.x[1]
    psi = model.x[2]
    v = model.x[3]
    delta = model.x[4]
    throttle = model.x[5]

    delta_dot = model.u[0]
    throttle_dot = model.u[1]

    a = model.f_expl_expr[3]

    coeffs = model.p


    Tm = r/G * (m*a + m*g*Cr + 1/2*rho*Cd*A*(v)**2)

    energy = Tm * v/r

    #pathYaw = atan(3*coeffs[3]*x1*x1 + 2*coeffs[2]*x1 + coeffs[1]) 
    pathYaw = 0 
    epsi = psi - pathYaw
    yPath =  coeffs[3]*x1**3 + coeffs[2]*x1**2 + coeffs[1]*x1 + coeffs[0]
    #yPath = 0
    cte = yPath - y1

    return vertcat(cte, epsi, v, delta, throttle, delta_dot, throttle_dot, energy)
