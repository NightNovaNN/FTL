! binder.f90
! Quark Fortran binder (optional backend)

module quark_binder
  use iso_c_binding
  implicit none

contains

  integer(c_int) function quark_fortran_opt(ir, count) &
      bind(C, name="quark_fortran_opt")

    integer(c_int), intent(inout) :: ir(*)
    integer(c_size_t), value :: count

    quark_fortran_opt = 0

    if (count <= 0) return

    call quark_fortran_handler(ir, count)

    quark_fortran_opt = 1
  end function quark_fortran_opt

end module quark_binder
