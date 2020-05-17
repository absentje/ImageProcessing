vec2 from_screen_coordinates(vec2 xy){
	return vec2((xy.x + 1.0) / 2.0, (xy.y + 1.0) / 2.0);
}

vec2 to_screen_coordinates(vec2 xy){
	return vec2(xy.x * 2.0 - 1.0, xy.y * 2.0 - 1.0);
}