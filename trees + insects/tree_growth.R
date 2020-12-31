setwd("C:/Users/Molly/Dropbox/uchicago/long-term paper/github_code")

data = read.csv("tree_rings.csv")

pdf("tree_growth.pdf", 14, 5)
par(mfrow = c(1, 2))

plot(data$Rings, data$DBH, pch = 20, cex = 2, xlim = c(0, 60), ylim = c(0, 60), xlab = "tree age (years)", ylab = "DBH (cm)", main = "Tree growth in Michigan")

DMax = 60
dhat = data$DBH/DMax

lin = lm(log((1-dhat)/dhat)~data$Rings)

beta0 = as.numeric(lin$coeff[1])
beta1 = as.numeric(lin$coeff[2])

age = seq(1,100,1)
dbh = c()
for(i in age){
	dbh[i] = DMax*(1/(1 + exp(beta0 + beta1*age[i])))
	}

lines(age, dbh, col = "red", lwd = 2)
text(20, 50, expression(paste(beta,"0 ="))); text(24, 50, round(beta0,2))
text(20, 47, expression(paste(beta,"1 ="))); text(25.5, 47, round(beta1,4))

### percentage changes:
new_dbh = c(1, dbh)
change = c()
for(i in 1:length(dbh)){
	change[i] = new_dbh[i+1]/new_dbh[i]
	}
#plot(c(0,age), new_dbh)
#plot(new_dbh, new_dbh)

write.csv(new_dbh, "dbh_increase_table.csv")

###
#kenkel data  ---- imagine you're in Manitoba:

k_Age = c(15, 20, 25, 30, 35, 41, 46, 51, 56)
k_DBH = c(4.65, 5.36, 6.07, 7.19, 8.64, 10.34, 12.06, 13.41, 14.34)

plot(k_Age, k_DBH, pch = 20, cex = 2, xlim = c(0, 60), ylim = c(0, 60), xlab = "tree age (years)", ylab = "DBH (cm)", main = "Tree growth in Manitoba")

DMax = 20
dhat = k_DBH/DMax

k_lin = lm(log((1-dhat)/dhat)~k_Age)

beta0 = as.numeric(k_lin$coeff[1])
beta1 = as.numeric(k_lin$coeff[2])

sim_age = seq(1,100,1)
sim_dbh = c()
for(i in sim_age){
	sim_dbh[i] = DMax*(1/(1 + exp(beta0 + beta1*sim_age[i])))
	}

lines(sim_age, sim_dbh, col = "red", lwd = 2)
text(20, 50, expression(paste(beta,"0 ="))); text(24, 50, round(beta0,2))
text(20, 47, expression(paste(beta,"1 ="))); text(25.5, 47, round(beta1,4))

dev.off()


##############   tree growth is suppressed following defoliation
##############   Gross 1992 regression: 

#   PG = .947 - .684*pct_defoliation   ## PG is (roughly) percent growth reduction

par(mfrow=c(1, 1))
pdf("growth_suppression.pdf")

pct_defoliation = seq(1, 100, 1)
PG = c()
for(i in pct_defoliation){
	PG[i] = .947 - .684*0.01*pct_defoliation[i]
	}

plot(pct_defoliation, 100*PG, type = "l", lwd = 2, xlim = c(0, 100), ylim = c(0, 100), cex = 2, cex.lab = 1.5, cex.axis = 1.5,
	xlab = "percent defoliation", ylab = "percent growth", main = "Growth suppression\n (see Gross 1992, Table A1, model 22)")
growth_suppression = cbind(pct_defoliation, PG)
write.csv(growth_suppression, "growth_suppression.csv")

dev.off()


