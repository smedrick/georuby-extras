require 'rubygems'
require 'geo_ruby'
require "#{File.dirname(__FILE__)}/../lib/georuby-extras"
require 'benchmark'

include GeoRuby::SimpleFeatures

@home = Point.from_lon_lat(-76.511,39.024)
@nyc = Point.from_lon_lat(-73.5,40.2)

Benchmark.bmbm(30) do |bm|
  bm.report("   c distance") {100000.times { @home.ellipsoidal_distance(@nyc) }}
  bm.report("ruby distance") {100000.times { @home.orig_ellipsoidal_distance(@nyc) }}
end

@poly_points = [[-95.81394, 41.008889], [-95.8103490000001, 41.0089209999999], [-95.8109810000001, 41.0072869999999], [-95.8113760000001, 41.00503], [-95.812187, 41.0017499999999], [-95.818804, 41.0017539999999], [-95.8187930000001, 41.0031709999998], [-95.8186090000002, 41.0038159999999], [-95.8186070000002, 41.008026], [-95.8185370000001, 41.008341], [-95.8183790000001, 41.008529], [-95.8181140000002, 41.008707], [-95.8178770000002, 41.0088039999998], [-95.817137, 41.00881], [-95.8158390000001, 41.0088089999999], [-95.815024, 41.0088289999999], [-95.8146770000001, 41.008836], [-95.8141700000001, 41.0089859999998], [-95.81394, 41.008889]]

@point = Point.from_coordinates([-95.8169174194336, 41.0077548921441])

@ring = LinearRing.from_coordinates(@poly_points)

Benchmark.bmbm(30) do |bm|
  bm.report("   c contains?") {100000.times { @ring.fast_contains?(@point) }}
  bm.report("ruby contains?") {100000.times { @ring.slow_contains?(@point) }}
end