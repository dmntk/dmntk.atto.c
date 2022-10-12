use std::fmt;

/// Plane containing edited characters.
pub struct Plane {}

impl fmt::Display for Plane {
  /// Converts a [Plane] into its string representation.
  fn fmt(&self, f: &mut fmt::Formatter<'_>) -> fmt::Result {
    write!(f, "???")
  }
}

impl Plane {
  /// Creates a new plane from specified text input.
  pub fn new(_text: String) -> Self {
    Self {}
  }
}
