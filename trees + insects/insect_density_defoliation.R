setwd("C:/Users/Molly/Dropbox/uchicago/long-term paper/github_code")


#### data was taken from Nealis and Lomic 1997, Fig. 2 

data = read.csv("nealis_defoliation.csv")	

defol = round(data$defoliation)
worms = (data$budworms) # this Nealis data is budworms per 100 shoots

model = glm((defol/100)~worms, family=binomial)

pdf("binomial_glm_budworms_defol.pdf", 7, 5)
par(mai=c(1, 1, .3, .3))
title = "Binomial GLM of budworms causing defolation"
plot(worms, log((defol/100)/(1 - (defol/100))), 
	ylab = 'defoliation measure', xlab = 'larvae per 100 buds', 
	cex.main = 1.6, cex.axis = 2, cex.lab = 2, cex = 2, pch = 20)

a = model$coefficients[1]
b = model$coefficients[2]

abline(a, b, lwd = 2)

dev.off()


#pdf("logit_scale_binomial_glm_budworms_defol.pdf")
#plot(worms, defol/100, cex.main = 1.6, cex.axis = 2, cex.lab = 2, cex = 2, pch = 20)
#worms2 = seq(min(worms), max(worms), by = .1)
#lines(worms2, exp(a + b*worms2)/(1 + exp(a + b*worms2)), lwd = 3)
#dev.off()