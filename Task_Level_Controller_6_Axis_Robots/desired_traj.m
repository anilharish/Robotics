%------------Function to compute Desired Trajectory-----------------%
function [Yd,Yddot,Yddot_double]=desired_traj(w,t)

Yd=zeros(3,1);
Yddot=zeros(3,1);
Yddot_double=zeros(3,1);

Yd(1,1)=-0.2165*cos(w*t)-0.56;
Yd(2,1)=0.25*sin(w*t);
Yd(3,1)=0.125*cos(w*t)-0.08;

Yddot(1,1)=0.2165*sin(w*t)*w;
Yddot(2,1)=0.25*cos(w*t)*w;
Yddot(3,1)=-0.125*sin(w*t)*w;

Yddot_double(1,1)=0.2165*cos(w*t)*w^2;
Yddot_double(2,1)=-0.25*sin(w*t)*w^2;
Yddot_double(3,1)=-0.125*cos(w*t)*w^2;
end