+This is a port of Matlab code over to C++
+This is a study in SABR.

+Issues:
+(1)  Results in Octave vs C++ VS2015 
+	 Differences in decimals.  Have not identified yet why?
	 
	 
+	 =====================================================
	 
+SABR Black-76 Equivalent Volatilies (%). Haug Book pg 270:

	p	    |	X=70	    |	X=80	    |	X=90	    |	X=100	    |	X=110	    |	X=120	    |	X=130	
----------  | ------------- | ---------     | ---------     | ---------     | ---------     | ---------     | --------- 
	-0.75	|	36.678324	|	34.18337	|	31.969147	|	30.000406	|	28.260363	|	26.745429	|	25.460042	
	-0.5	|	35.17378	|	33.114696	|	31.399449	|	30.00007	|	28.898052	|	28.074855	|	27.505726	
	-0.25	|	33.509761	|	31.952084	|	30.795686	|	29.999994	|	29.520725	|	29.306531	|	29.302682	
	0	    |	31.652567	|	30.682965	|	30.157598	|	30	        |	30.126458	|	30.456642	|	30.92308	
	0.25	|	29.546048	|	29.288287	|	29.48468	|	30.000008	|	30.713715	|	31.53576	|	32.406472	
	0.5	    |	27.086116	|	27.737585	|	28.776021	|	29.999951	|	31.281185	|	32.551056	|	33.776878	
	0.75	|	24.040084	|	25.97829	|	28.030273	|	29.999873	|	31.827825	|	33.507644	|	35.050007	
																	
+Alpha Parameter Values used by SABR Black-76 Equivalent Volatilies, above.
																
	|	p	    |	X=70	    |	X=80	    |	X=90	    |	X=100	    |	X=110	    |	X=120	    |	X=130	
    | --------- | ---------     | ---------     | ---------     | ---------     | ---------     | ---------     | --------- 
	|	-0.75	|	0.305235	|	0.305235	|	0.305235	|	0.305235	|	0.305235	|	0.305235	|	0.305235	
	|	-0.5	|	0.302257	|	0.302257	|	0.302257	|	0.302257	|	0.302257	|	0.302257	|	0.302257	
	|	-0.25	|	0.299951	|	0.299951	|	0.299951	|	0.299951	|	0.299951	|	0.299951	|	0.299951	
	|	0	    |	0.298278	|	0.298278	|	0.298278	|	0.298278	|	0.298278	|	0.298278	|	0.298278	
	|	0.25	|	0.297207	|	0.297207	|	0.297207	|	0.297207	|	0.297207	|	0.297207	|	0.297207	
	|	0.5	    |	0.296717	|	0.296717	|	0.296717	|	0.296717	|	0.296717	|	0.296717	|	0.296717	
	|	0.75	|	0.296794	|	0.296794	|	0.296794	|	0.296794	|	0.296794	|	0.296794	|	0.296794	
																	
+Black-76 Put Prices r:0.020000										
																	
	|	p	|	|	|	X=70	|	|	|	X=80	|	|	|	X=90	|	X=100	X=130
    | --------- | --------- | --------- | --------- | --------- | --------- | --------- | --------- | --------- |
	|	-0.75	|	|0.826769	|	|2.050543	|	|4.411993	|	8.362983	|	14.14351	|	21.624893	|	30.355513	
	|	-0.5	|	|0.696645	|	|1.879802	|	|4.277698	|	8.36289	|	14.309785	|	21.884927	|	30.598439	
	|	-0.25	|	|0.565428	|	|1.699586	|	|4.135938	|	8.362869	|	14.472881	|	22.135225	|	30.840911	
	|	0	|	|0.435410	|	|1.509967	|	|3.986790	|	8.36287	|	14.632193	|	22.376342	|	31.081002	
	|	0.25	|	|0.309673	|	|1.310885	|	|3.830296	|	8.362872	|	14.787226	|	22.608509	|	31.317215	
	|	0.5	|	|0.192635	|	|1.102052	|	|3.666433	|	8.362857	|	14.937546	|	22.83177	|	31.548329	
	|	0.75	|	|0.091258	|	|0.882768	|	|3.495115	|	8.362835	|	15.082796	|	23.046082	|	31.773332	
																	
+Black-76 Call Prices r:0.020000										
																	
	|	p	|	X=70	|	X=80	|	X=90	|	X=100	|	X=110	|	X=120	|	X=130	
    | --------- | --------- | --------- | --------- | --------- | --------- | --------- | --------- | --------- |
	|	-0.75	|	30.528264	|	21.85154	|	14.312491	|	8.362983	|	4.243012	|	1.823896	|	0.654018	
	|	-0.5	|	30.39814	|	21.680799	|	14.178196	|	8.36289	|	4.409287	|	2.08393	|	0.896944	
	|	-0.25	|	30.266923	|	21.500583	|	14.036436	|	8.362869	|	4.572382	|	2.334228	|	1.139416	
	|	0	|	30.136905	|	21.310963	|	13.887288	|	8.36287	|	4.731695	|	2.575345	|	1.379507	
	|	0.25	|	30.011168	|	21.111882	|	13.730794	|	8.362872	|	4.886728	|	2.807512	|	1.61572	
	|	0.5	|	29.89413	|	20.903049	|	13.566931	|	8.362857	|	5.037047	|	3.030773	|	1.846834	
	|	0.75	|	29.792753	|	20.683765	|	13.395614	|	8.362835	|	5.182298	|	3.245086	|	2.071838	
																	
+ diff in Black-76 Put Call Parity Eqn: (C-P) - (F-K)exp(-rT) r:0.020000 F: 100.000000 T:0.500000
																	
	|	p	|	X=70	|	X=80	|	X=90	|	X=100	|	X=110	|	X=120	|	X=130	
    | --------- | --------- | --------- | --------- | --------- | --------- | --------- | --------- | --------- |
	|	-0.75	|	0	|	0	|	0	|	0	|	0	|	0	|	0	
	|	-0.5	|	0	|	0	|	0	|	0	|	0	|	0	|	0	
	|	-0.25	|	0	|	0	|	0	|	0	|	0	|	0	|	0	
	|	0	|	0	|	0	|	0	|	0	|	0	|	0	|	0	
	|	0.25	|	0	|	0	|	0	|	0	|	0	|	0	|	0	
	|	0.5	|	0	|	0	|	0	|	0	|	0	|	0	|	0	
	|	0.75	|	0	|	0	|	0	|	0	|	0	|	0	|	0	
