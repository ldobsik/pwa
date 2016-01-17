function [y e]=pwa_grid(f,g,w)
% Finds a piecewise affine approximation of f over the grid g by optimizing
% the sum of einf over the intervals defined by the grid.
%
% Returns the function values vector y and einf over the particular intervals.
% Solving by dual simplex method takes ~O(len(f)*len(g)).
% f = function values vector
% g = control points enumeration vector (must be sorted and must include
%     the boundary points 0 and N)
% w = vector of relative point tolerances (optional)
% y = y at control points
% e = l-inf error at partition intervals
%tic
  N = length(f);
  M = length(g);

  if nargin < 3
    w = ones(N,1);
  end

  % the solution base = the curvature constraint nullspace
  % incorporating the solution base into inequalities eliminates the equalities constraints
  nullD = pwa_base(g);

  % construct matrices A and B, so that each interval, its boundary points
  % including, has its l-inf norm
  ctrlpoints  = length(g);
  intervals   = ctrlpoints-1;
  constraints = N+intervals-1;

  Ae = sparse([],[],[],constraints,intervals);
  Ay = sparse([],[],[],constraints,ctrlpoints);

  B = zeros(constraints,1);
  col = 1;
  row = 1;
  po = g(1);
  for p=g(2:end)'
      wid = p - po + 1;
      Ae(row:(row+wid-1),col) = w(1+(po:p),1);
      Ay(row:(row+wid-1),:)   = nullD(1+(po:p),:);
      B (row:(row+wid-1),1)   = f(1+(po:p),1);
      po = p;
      col = col + 1;
      row = row + wid;
  end

  % constructing the matrices A, B
  A = [[-Ae, Ay];
       [-Ae,-Ay]];
  B = [ B;
       -B];

  % cost function = sum of l-inf norms over the partition intervals
  C = sparse([ones(intervals,1); zeros(ctrlpoints,1)]);
  % norm of error expressions are inequalities "less than"
  % curvature is equality (must be equal to zero)

  ctype   = char(["U"*ones(2*constraints,1)]);
  vartype = char(["C"*ones(intervals,1);"C"*ones(ctrlpoints,1)]);
  varlb   = [    zeros(intervals,1); -Inf*ones(ctrlpoints,1)];
  varub   = [+Inf*ones(intervals,1); +Inf*ones(ctrlpoints,1)];
  param.msglev = 2;
  param.tolbnd = 1e-6;
  param.toldj  = 1e-6;
  param.dual   = 1;

  % norm of error expressions are inequalities "less than"
  % curvature is equality (must be equal to zero)
  [yopt, fmin, status, extra] = glpk (C, A, B, varlb, varub, ctype, vartype, 1, param);

  e = yopt(1:intervals);
  % convert the solution from the solution base back to the canonical base
  y = nullD*yopt((1:ctrlpoints)+intervals);
%toc
end
