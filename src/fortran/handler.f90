! handler.f90
! Quark Fortran optimization handlers

module quark_handler
  use iso_c_binding
  implicit none

contains

  subroutine quark_fortran_handler(ir, count) &
      bind(C, name="quark_fortran_handler")

    integer(c_int), intent(inout) :: ir(*)
    integer(c_size_t), value :: count
    integer(c_size_t) :: i

    if (count <= 0) return

    i = 1
    do while (i <= count)
      ! no-op placeholder
      i = i + 1
    end do
  end subroutine quark_fortran_handler

end module quark_handler
