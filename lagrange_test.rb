require "test/unit"
require "./lagrange.rb"

class LagrangeTest < Test::Unit::TestCase
  def test_zero_order
    lagrange = Lagrange.new([1, 2])
    assert_equal [2], lagrange.coefficients
  end
  
  def test_first_order
    lagrange = Lagrange.new([1, 1], [2, 3.5])
    assert_equal [-1.5, 2.5], lagrange.coefficients
  end
  
  def test_second_order
    lagrange = Lagrange.new([1, 1], [2, 4], [3, 9])
    assert_equal [0.0, 0.0, 1.0], lagrange.coefficients
  end
end