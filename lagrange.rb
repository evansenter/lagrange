require "complex"

class Lagrange  
  attr_reader :points
  
  def initialize(*points)
    @points = points
  end
  
  def coefficients
    if points.length == 1
      points.map(&:last)
    else
      coefficient_array = (0...points.length).map(&method(:basis_coefficients))
      coefficient_array.first.zip(*coefficient_array[1..-1]).map { |coefficients| coefficients.inject(&sum) }
    end
  end
  
  def basis_coefficients(index_to_skip)
    x_values     = points.map(&:first).each_with_index.reject { |points, index| index == index_to_skip }.map(&:first)
    constant     = (points[index_to_skip].last.kind_of?(Integer) ? points[index_to_skip].last.to_f : points[index_to_skip].last) / x_values.map { |x| points[index_to_skip].first - x }.inject(&scalar)
    coefficients = x_values.map(&scalar(-1)).inject([1.0]) do |coefficients, x|
      ([0.0] + coefficients).zip(coefficients.map(&scalar(x))).map do |array|
        array.compact.inject(&sum)
      end
    end
    
    coefficients.map(&scalar(constant))
  end
  
  def sum
    ->(a, b) { a + b }
  end
  
  def scalar(a = nil)
    a ? ->(b) { a * b } : ->(a, b) { a * b }
  end
end