#include "tmatrix.h"

#include <gtest.h>

TEST(TDynamicMatrix, can_create_matrix_with_positive_length) {

	ASSERT_NO_THROW(TDynamicMatrix<int> m(5));
}

TEST(TDynamicMatrix, cant_create_too_large_matrix) {

	ASSERT_ANY_THROW(TDynamicMatrix<int> m(MAX_MATRIX_SIZE + 1));
}

TEST(TDynamicMatrix, throws_when_create_matrix_with_negative_length) {

	ASSERT_ANY_THROW(TDynamicMatrix<int> m(-5));
}

TEST(TDynamicMatrix, can_create_copied_matrix) {

	TDynamicMatrix<int> m(5);
	ASSERT_NO_THROW(TDynamicMatrix<int> m_1(m));
}

TEST(TDynamicMatrix, copied_matrix_is_equal_to_source_one) {//

	TDynamicMatrix<int> m_1(5);
	m_1[1][1] = 3;
	m_1[3][3] = 5;
	TDynamicMatrix<int> m_2(m_1);
	EXPECT_EQ(m_1, m_2);
}

TEST(TDynamicMatrix, copied_matrix_has_its_own_memory){// with vector too problems 

	TDynamicMatrix<int> m_1(5);
	TDynamicMatrix<int> m_2(m_1);
	EXPECT_TRUE(&m_1[0][0] != &m_2[0][0]);
}

TEST(TDynamicMatrix, can_get_size) {

	TDynamicMatrix<int> m(5);
	EXPECT_EQ(5, m.size());
}

TEST(TDynamicMatrix, can_set_and_get_element) {

	TDynamicMatrix<int> m(5);
	m[0][1] = 2;
	EXPECT_EQ(2, m[0][1]);

}

TEST(TDynamicMatrix, throws_when_set_element_with_negative_index) {

	TDynamicMatrix<int> m(5);
	EXPECT_ANY_THROW(m[-5][3] = -5);
}

TEST(TDynamicMatrix, throws_when_set_element_with_too_large_index) {

	TDynamicMatrix<int> m(5);
	EXPECT_ANY_THROW(m[10][3] = 5);
}

TEST(TDynamicMatrix, can_assign_matrix_to_itself) {

	TDynamicMatrix<int> m(2);
	m[0][0] = 5;
	m[0][1] = 5;
	m[1][0] = 5;
	m[1][1] = 5;
	m = m;
	EXPECT_EQ(m, m);
}

TEST(TDynamicMatrix, can_assign_matrices_of_equal_size) {

	TDynamicMatrix<int> m_1(5);
	TDynamicMatrix<int> m_2(5);
	EXPECT_NO_THROW(m_1 = m_2);
}

TEST(TDynamicMatrix, assign_operator_change_matrix_size) {

	TDynamicMatrix<int> m1(1), m2(5);
	m1 = m2;
	EXPECT_EQ(m1.size(), 5);
}

TEST(TDynamicMatrix, can_assign_matrices_of_different_size) {

	TDynamicMatrix<int> m_1(10);
	TDynamicMatrix<int> m_2(5);
	m_1 = m_2;
	EXPECT_EQ(m_1, m_2);
}

TEST(TDynamicMatrix, compare_equal_matrices_return_true) {

	TDynamicMatrix<int> m_1(10);
	TDynamicMatrix<int> m_2(m_1);
	EXPECT_EQ(m_1 == m_2, true);
}

TEST(TDynamicMatrix, compare_matrix_with_itself_return_true) {

	TDynamicMatrix<int> m_1(5);
	EXPECT_EQ(m_1 == m_1, true);
}

TEST(TDynamicMatrix, matrices_with_different_size_are_not_equal) {

	TDynamicMatrix<int> m_1(10);
	TDynamicMatrix<int> m_2(5);
	EXPECT_EQ(m_1 == m_2, false);
}

TEST(TDynamicMatrix, can_add_matrices_with_equal_size) {

	TDynamicMatrix<int> m_1(5);
	m_1[3][3] = 10;
	TDynamicMatrix<int> m_2(5);
	m_2[3][3] = 5;
	TDynamicMatrix<int> m = m_1 + m_2;
	TDynamicMatrix<int> res(5);
	res[3][3] = 15;
	EXPECT_EQ(m, res);
}

TEST(TDynamicMatrix, cant_add_matrices_with_not_equal_size) {

	TDynamicMatrix<int> m_1(5);
	TDynamicMatrix<int> m_2(10);
	EXPECT_ANY_THROW(m_1 + m_2);
}

TEST(TDynamicMatrix, can_subtract_matrices_with_equal_size) {

	TDynamicMatrix<int> m_1(5);
	TDynamicMatrix<int> m_2(5);
	m_1[3][3] = 10;
	m_2[3][3] = 5;
	TDynamicMatrix<int> m = m_1 - m_2;
	TDynamicMatrix<int> res(5);
	res[3][3] = 5;
	EXPECT_EQ(m, res);
}

TEST(TDynamicMatrix, cant_subtract_matrixes_with_not_equal_size) {

	TDynamicMatrix<int> m_1(5);
	TDynamicMatrix<int> m_2(10);
	EXPECT_ANY_THROW(m_1 - m_2);
}