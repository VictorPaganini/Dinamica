///============================================================================
// Name        : Teste.cpp
// Author      : Victor
// Version     :
// Copyright   : Your copyright notice
// Description : 3 GL
//============================================================================

#include <iostream>
#include <cstdlib>
#include <string>
#include <vector>
#include <cmath>
#include <fstream>	


class connection

{
    public:
    double a, b;

};

class node

{
    public:
    double x, y, z;

};


///////////////////////////////////////
//									 //
//  LEITURA DO ARQUIVO DE ENTRADA	 //	
//									 //	
///////////////////////////////////////
	int numElem, numNodes, numTimesteps;
    double x[3],v[3],a[3],k[3],cForce[3],vForce[3],w[3],beta,gama,timestep,m;
    std::string input_file, output_file,line;
    std::vector<double> cx;
    std::vector<double> cy;
    std::vector<double> cz;
    std::vector<double> conec1;
    std::vector<double> conec2; 

    output_file = "mirror.txt";
    input_file = "input_test.txt";

    std::ifstream inputData(input_file.c_str());
    std::ofstream outputData(output_file.c_str());

    getline(inputData,line),getline(inputData,line),getline(inputData,line);

    //aspectos gerais
    inputData >> numElem >> numNodes >> numTimesteps;

    outputData << "Número de elementos: " << numElem << std::endl;
    outputData << "Número de nós: " << numNodes << std::endl;
    outputData << "Número de timesteps: " << numTimesteps << std::endl;

    getline(inputData,line);getline(inputData,line);getline(inputData,line);
    getline(inputData,line);getline(inputData,line);;

    //condicoes iniciais    
    inputData >> v[0] >> v[1] >> v[2];

    outputData << "Velocidade em X: " << v[0] << std::endl; 
    outputData << "Velocidade em Y: " << v[1] << std::endl; 
    outputData << "Velocidade rotacional: " << v[2] << std::endl; 

    getline(inputData,line);getline(inputData,line);getline(inputData,line);
    getline(inputData,line);

    //inputData >> a[0] >> a[1] >> a[2];

    //outputData << "Aceleracao inicial em X: " << a[0] << std::endl; 
    //outputData << "Aceleracao inicial em Y: " << a[1] << std::endl; 
    //outputData << "Aceleracao radial inicial: " << a[2] << std::endl;

    getline(inputData,line);getline(inputData,line);getline(inputData,line);
    getline(inputData,line);

    inputData >> x[0] >> x[1] >> x[2];
    
    outputData << "Deslocamento inicial X: " << x[0] << std::endl; 
    outputData << "Descolamento inicial Y: " << x[1] << std::endl; 
    outputData << "Rotacao inicial: " << x[2] << std::endl;

    getline(inputData,line);getline(inputData,line);getline(inputData,line);
    getline(inputData,line);getline(inputData,line);

    //caracteristicas da secao
    inputData >> m >> k[0] >> k[1] >> k[2];

    outputData << "Massa: " << m << std::endl;
    outputData << "K X: " << k[0] << std::endl; 
    outputData << "K Y: " << k[1] << std::endl; 
    outputData << "Kteta: " << k[2] << std::endl;

    getline(inputData,line);getline(inputData,line);getline(inputData,line);
    getline(inputData,line);getline(inputData,line);

    //metodo numerico
    inputData >> timestep >> gama >> beta;

    outputData << "Timestep: " << timestep << std::endl; 
    outputData << "Gama: " << gama << std::endl; 
    outputData << "Beta: " << beta << std::endl;

    getline(inputData,line);getline(inputData,line);getline(inputData,line);
    getline(inputData,line);getline(inputData,line);getline(inputData,line);   
    getline(inputData,line); 

    //forcas aplicadas
    inputData >> cForce[0] >> vForce[0] >> w[0] >> cForce[1] >> vForce[1] >> w[1] >> cForce[2] >> vForce[2] >> w[2];

    outputData << "Fx(A+Bsinwt) A:" << cForce[0]<< " B: " << vForce[0] << " w: " << w[0] << std::endl; 
    outputData << "Fy(A+Bsinw) A:" << cForce[1]<< " B: " << vForce[1] << " w: " << w[1] << std::endl;
    outputData << "My(A+Bsinwt) A:" << cForce[2]<< " B:" << vForce[2] << " w:" << w[2] << std::endl;

    getline(inputData,line);getline(inputData,line);getline(inputData,line);getline(inputData,line);

    //coordenadas
    outputData << "Coordenadas \n";
    for (int i=0; i<numNodes; i++){

        node node;
        inputData >> node.x >> node.y >> node.z;
        //outputData << node.x << " " << node.y << " "<< node.z << " \n\n";
        cx.push_back(node.x);
        cy.push_back(node.y);
        cz.push_back(node.z);
    }

    for (int i=0; i<numNodes; i++){

        outputData << cx[i] << " " << cy[i] << " " << cz[i] << "\n\n";

    }

    getline(inputData,line);getline(inputData,line);getline(inputData,line);getline(inputData,line);

    //conectividade
    outputData << "Conectividade \n";
    for (int i=0; i<numElem; i++){

        connection connection;
        inputData >> connection.a >> connection.b;
        //outputData << conection.a << " " << conection.b;
        conec1.push_back(connection.a);
        conec2.push_back(connection.b);

    }

    for (int i=0; i<4=numElem; i++){

        outputData << conec1[i] << " " << conec2[i] << "\n\n";

    }
	    
    getline(inputData,line);getline(inputData,line);getline(inputData,line);

    node centro;

    inputData >> centro.x >> centro.y >> centro.z;
    outputData << "Centro \n";
    outputData << centro.x << " " << centro.y << " " << centro.z;


	std::vector<double> force(double A,double B, double C, double D,double E,double F,double w,double t) {

		std::vector<double> force;
		force.push_back(A+B*sin(w*t));
		force.push_back(C+D*sin(w*t));
		force.push_back(E+F*sin(w*t));

		return force;
	}		

//////////////////////////
//						//	
//	PRÉ PROCESSAMENTO   //
//						//
//////////////////////////

//calculo de alfa inicial

	std::vector<double> alfa;

	for (int i=0; i<numNodes; i++);

		double delta_cx = centro.x - cx(i);
		double delta_cx = centro.x - cx(i);

		if 
	double xi,vi,m,dt,k,c,beta,gama,wn,A,B,C,D,E,F;
	char filename[] = "saida.csv";

	A=1;
	B=0.;
	C=1.;
	D=0;
	E=1.;
	F=0.;
	xi = 0.;
	vi = 0.;
	m = 2.;
	dt = 0.0001;
	k = 5.;
	c = 0.;
	beta=.25;
	gama=.5;
	wn=sqrt(k/m);

	std::vector<double> InitialForce = force(A, B, C, D, E, F, wn,0);

	int num=10;

	double xPrev[3], vPrev[3], aPrev[3], x[3], v[3], a[3];

	// aceleracoes iniciais
	a[0]=(InitialForce[0]-k*xi-c*vi)/m;
	a[1]=(InitialForce[1]-k*xi-c*vi)/m;
	a[2]=(InitialForce[2]-k*xi-c*vi)/m;
	
	for (int i=0; i<3; i++){;
	
		xPrev[i] = x[i];
		vPrev[i] = v[i];
		aPrev[i] = a[i];	
	}

	std::ofstream outputfile;
	outputfile.open(filename);
	outputfile << 0 <<";" << x[0] << ";"<< x[1] <<";"<< x[2] << std::endl;


	for (int i=1; i<=num; i++){

		double t=t+dt;
		std::vector<double> InstantForce=force(A, B, C, D, E, F, wn,t);

	
		for (int i=0; i<3;i++){

			x[i]=(InstantForce[i] + ((1./beta)*(m/(dt*dt))+(gama/beta)*(c/dt))*xPrev[i] +((1./beta)*(m/dt)+((gama/beta)-1.)*c)*vPrev[i]+((1./(2.*beta)-1.)*m+(gama/(beta)-1.)*c*dt)*aPrev[i])
				/((1./beta)*m/(dt*dt)+k+(gama/beta)*(c/dt));

			v[i]=((gama/beta)/dt)*x[0]-((gama/beta)/dt)*xPrev[i]-((gama/beta)-1.)*vPrev[i]
			-((gama/(2.*beta))-1.)*dt*aPrev[i];

			a[i] = (InstantForce[i] - k*x[i]-c*v[i])/m;

			}

		outputfile << t <<";" << x[0] << ";"<< x[1] <<";"<< x[2] << std::endl;


		for (int i=0; i<3; i++){;
	
			xPrev[i] = x[i];
			vPrev[i] = v[i];
			aPrev[i] = a[i];	
		}
	}
	outputfile.close();
	return 0;

}