function dydt = odefn(t,y,Y_int,w)
dydt=zeros(6,1)
%Desired Position and Velocity
[Yd,Yddot,Yddot_double]=desired_traj(w,t);   
%To Compute Jacobian
[J,Jdot,qdot]=jacobian(y(1:3),Y_int(4:6));
y(4:6)=qdot.';
%To Compute Dynamics
[D,C,g] = dynamic(y(1:3),qdot);
% Parametric Error
error_per=30/100*eye(3); 
D=error_per*D;
C=error_per*C;
g=error_per*g;
%% Linear PD controller
e=Yd-Y_int(1:3).';
edot=Yddot-Y_int(4:6).';
kd=[3.5 3.0 4.0]*eye(3);
kp=[2.0 1.5 2.5]*eye(3);
u=Yddot_double+(kd*edot)+(kp*e);
%% Non-linear Feedback
Tou=(D*pinv(J)*u)-(D*pinv(J)*Jdot*qdot)+(C*qdot)+g;
%% Sysyem Dynamics
dydt(1)=y(4);%theta1-dot
dydt(2)=y(5);%theta2-dot
dydt(3)=y(6);%theta3-dot
qdot_double=pinv(D)*(Tou-(C*qdot)-g);
dydt(4)=qdot_double(1);
end