function [x_vec y_vec] = pwa_approx_roi(x_tab, y_tab, y_roi, x_step)

% find the x_roi from the image of y_roi
x_minmax = interp1(y_tab, x_tab, y_roi, 'linear','extrap');   
x_roi_min = floor(min(x_minmax));
x_roi_max = ceil(max(x_minmax));
x_roi_span = (x_roi_max-x_roi_min);
% round up the interval size to a multiple of x_step 
x_span = x_step * ceil(x_roi_span/x_step);

% calculate the number of fill-in values due to rounding to a multiple of x_step
x_fill_in = x_span - x_roi_span;

% the new, rounded, wider, interval has the ROI inteval in the middle
x_min = x_roi_min - floor(x_fill_in/2);
x_max = x_min + x_span;
x  = (x_min:x_max)';

% relax the weights for points outside ROI
x_weight = ones(length(x), 1);
x_weight(find((x < x_roi_min) | (x > x_roi_max))) = 1e6; % set relative tolerance to 1e6

% find y values for the whole range of x values
y = interp1(x_tab, y_tab, x, 'linear', 'extrap');
x_grid = [0:x_step:x_span]';

% find approximation on the grid
[y_approx e] = pwa_grid(y, x_grid, x_weight);

% return approximation at grid points 
x_vec  = x(x_grid+1);
y_vec = y_approx(x_grid+1);
end
