
### defoliation from Fig. 1 in McCullough et al, 1996

defol = c(0, 26, 55.5, 35)

### mortality from Fig. 2

mort = c(1e-3, .01, .035, .08)

### they find that predictors of mortality the degree of defoliation, from the current and previous year 

model = lm(log((1 - mort[2:4])/mort[2:4])~defol[2:4]+defol[1:3])

beta0 = as.numeric(model$coefficients[1])
beta1 = as.numeric(model$coefficients[2])
beta2 = as.numeric(model$coefficients[3])

thing = beta0 + beta1*defol[2:4] + beta2*defol[1:3]

P_mort = 1 /(1 + exp(thing))

