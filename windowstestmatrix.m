A=[
11 12 45 12 01 45 79 32;
54 56 87 31 32 65 45 81;
98 78 65 14 23 65 84 00;
78 98 95 32 12 54 87 38;
15 65 60 91 79 36 45 22;
26 78 25 62 02 54 78 63;
33 95 78 14 58 78 25 19;
36 89 01 54 87 62 95 72;
];

AA=[
11 12 45 12 01 45 79 32;
54 56 87 31 32 65 45 81;
98 78 65 14 23 65 84 00;
78 98 95 32 12 54 87 38;
15 65 60 91 79 36 45 22;
26 78 25 62 02 54 78 63;
33 95 78 14 58 78 25 19;
36 89 01 54 87 62 95 72;
];

D = [1];

C = A + AA
C = A - AA
C = A * AA
A = A / AA
D = A ./ AA
D = A ./ 10
D = 10 ./ A

