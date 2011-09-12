class Lagrange
  # ruby-1.9.2-p290 :419 > l = Lagrange.new([1, 1], [2, 4], [3, 9])
  #  => #<Lagrange:0x007fce6c1b0188 @points=[[1, 1], [2, 4], [3, 9]]> 
  # ruby-1.9.2-p290 :420 > l.coefficients
  #  => [0.0, 0.0, 1.0] 
  
  attr_reader :points
  
  def initialize(*points)
    @points = points
    raise ArgumentError.new("Must provide at least 2 points") unless points.length >= 2
  end
  
  def coefficients
    coefficient_array = (0...points.length).map(&method(:basis_coefficients))
    
    coefficient_array.first.zip(*coefficient_array[1..-1]).map { |coefficients| coefficients.inject(&sum) }
  end
  
  def basis_coefficients(index_to_skip)
    x_values     = points.map(&:first).each_with_index.reject { |points, index| index == index_to_skip }.map(&:first)
    constant     = points[index_to_skip].last.to_f / x_values.map { |x| points[index_to_skip].first - x }.inject(&scalar)
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