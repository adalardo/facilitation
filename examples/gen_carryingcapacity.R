numstages <- 3
deathrates <- c(0.28025,0.00875,0.138)  # death rates for seed, sapling and adult
growthrates <- c(0.35865,0.0875)      # transition rates seed-->sapling and sapling-->adult
reproductionrate <- 1.6        # reproduction rate (only adult)
dispersalradius <- 1.5          # average distance a seed falls from the parent (distance is gaussian)
times <- seq(10,200,1.5)         # array of times of interest
initialpop <- c(80,40,10,0)	# initial pop. sizes for the 3 stages plus the facilitator species
facindex <- c(0,0.8)            # this will be the values by which facilitator decreases seeds and seedlings deathrates
effects <- c(0,0,0, 0,-0.01,0, 0,0,-0.08) # the effects reducing deathrate (negative values increase deathrates)
radius <- c(0,0.2,2,3)        # this are the distances up to which the individuals can have effect on others, by stage + facilitator
h <- 20                       # arena height
w <- 20                       # arena width

dt <- facByRates(times=times, n=numstages, Ds=deathrates, Gs=growthrates, dispersal=dispersalradius, R=reproductionrate, 
		 interactions=effects, fac=facindex, init=initialpop, rad=radius, h=h, w=w)

ab <- abundance_matrix(dt$data)
stackplot(ab[,1:3],70)
saveGIF(spatialplot(dt),interval=0.1,movie.name="competition.gif") 
