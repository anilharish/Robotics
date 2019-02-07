%--------Function for Jacobian and Derivative----------%
function [J,Jdot,qdot]=jacobian(q,Ydot)
Ydot=[0 0 0];
J=zeros(3,3);
Jdot=zeros(3,3);

J(1,1)= 0.02032*sin(q(1))*cos(q(2)+q(3)) - 0.43307*sin(q(1))*sin(q(2)+q(3)) - 0.4318*sin(q(1))*cos(q(2)) -0.14909*cos(q(1));
J(1,2)= 0.02032*cos(q(1))*sin(q(2)+q(3)) + 0.43307*cos(q(1))*cos(q(2)+q(3)) - 0.4318*cos(q(1))*sin(q(2));
J(1,3)= 0.02032*cos(q(1))*sin(q(2)+q(3)) + 0.43307*cos(q(1))*cos(q(2)+q(3));

J(2,1)= -0.02032*cos(q(1))*sin(q(2)+q(3)) + 0.43307*cos(q(1))*sin(q(2)+q(3)) + 0.4318*cos(q(1))*cos(q(2)) - 0.14909*sin(q(1));
J(2,2)= 0.02032*sin(q(1))*sin(q(2)+q(3)) + 0.43307*sin(q(1))*cos(q(2)+q(3)) - 0.4318*sin(q(1))*sin(q(2));
J(2,3)= 0.02032*sin(q(1))*sin(q(2)+q(3)) + 0.43307*sin(q(1))*cos(q(2)+q(3));

J(3,1)= 0;
J(3,2)= 0.02032*cos(q(2)+q(3)) - 0.43307*sin(q(2)+q(3)) - 0.4318*cos(q(2));
J(3,3)= 0.02032*cos(q(2)+q(3)) - 0.43307*sin(q(2)+q(3));

Jdot(1,1)= 0.02032*cos(q(1))*cos(q(2)+q(3)) - 0.43307*cos(q(1))*sin(q(2)+q(3)) - 0.4318*cos(q(1))*cos(q(2)) +0.14909*sin(q(1));
Jdot(1,2)= 0.02032*cos(q(1))*cos(q(2)+q(3)) - 0.43307*cos(q(1))*sin(q(2)+q(3)) - 0.4318*cos(q(1))*cos(q(2));
Jdot(1,3)= 0.02032*cos(q(1))*cos(q(2)+q(3)) - 0.43307*cos(q(1))*sin(q(2)+q(3));

Jdot(2,1)= 0.02032*sin(q(1))*sin(q(2)+q(3)) - 0.43307*sin(q(1))*sin(q(2)+q(3)) - 0.4318*sin(q(1))*cos(q(2)) - 0.14909*cos(q(1));
Jdot(2,2)= 0.02032*sin(q(1))*cos(q(2)+q(3)) - 0.43307*sin(q(1))*sin(q(2)+q(3)) - 0.4318*sin(q(1))*cos(q(2));
Jdot(2,3)= 0.02032*sin(q(1))*cos(q(2)+q(3)) - 0.43307*sin(q(1))*sin(q(2)+q(3));

Jdot(3,1)= 0;
Jdot(3,2)= -0.02032*sin(q(2)+q(3)) - 0.43307*cos(q(2)+q(3)) + 0.4318*sin(q(2));
Jdot(3,3)= -0.02032*sin(q(2)+q(3)) - 0.43307*cos(q(2)+q(3));

qdot= inv(J)*Ydot.';
end
